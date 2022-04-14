#!/usr/bin/env python3
# ****************************************************************************
# Copyright 2019 The Apollo Authors. All Rights Reserved.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ****************************************************************************

import math
import os
import sys
import time

from cyber.python.cyber_py3 import cyber_time
from cyber.python.cyber_py3 import cyber

def print_channel_type(channel_name):
    msgtype = cyber.ChannelUtils.get_msgtype(channel_name)
    print(channel_name, " type is [", msgtype, "]")


def _channel_cmd_type(argv):
    """
    Command-line parsing for 'cyber_channel type channelname' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel type channelname")
    (options, args) = parser.parse_args(args)
    if len(args) > 1:
        parser.error("you may only specify one input channel")
    elif len(args) == 0:
        parser.error("channelname must be specified")
    print_channel_type(args[0])


class CyberChannelBw(object):

    def __init__(self, window_size=100):
        import threading
        self.lock = threading.Lock()
        self.sizes = []
        self.times = []
        self.window_size = window_size
        if window_size <= 0 or window_size > 50000:
            self.window_size = 100
        print("bw window_size: ", self.window_size)

    def callback_bw(self, rawdata):
        with self.lock:
            t = time.time()
            self.times.append(t)
            self.sizes.append(len(rawdata))
            assert(len(self.times) == len(self.sizes))

            if len(self.times) > self.window_size:
                self.times.pop(0)
                self.sizes.pop(0)

    def print_bw(self):
        if len(self.times) < 2:
            return
        with self.lock:
            n = len(self.times)
            tn = time.time()
            t0 = self.times[0]

            total = sum(self.sizes)
            bytes_per_s = total / (tn - t0)
            mean = total / n

            max_s = max(self.sizes)
            min_s = min(self.sizes)

        if bytes_per_s < 1000:
            bw, mean, min_s, max_s = [
                "%.2fB" % v for v in [bytes_per_s, mean, min_s, max_s]]
        elif bytes_per_s < 1000000:
            bw, mean, min_s, max_s = ["%.2fKB" % (v / 1000)
                                      for v in [bytes_per_s, mean, min_s, max_s]]
        else:
            bw, mean, min_s, max_s = ["%.2fMB" % (v / 1000000)
                                      for v in [bytes_per_s, mean, min_s, max_s]]

        print("average: %s/s\n\tmean: %s min: %s max: %s window: %s" %
              (bw, mean, min_s, max_s, n))


def channel_bw(channel_name, window_size):
    rt = CyberChannelBw(window_size)
    node_bw = cyber.Node("listener_node_bw")
    node_bw.create_rawdata_reader(channel_name, rt.callback_bw)
    print("reader to [%s]" % channel_name)
    while not cyber.is_shutdown():
        time.sleep(1.0)
        rt.print_bw()


def _channel_cmd_bw(argv):
    """
    Command-line parsing for 'cyber_channel bw' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel bw channelname")
    parser.add_option("-w", "--window",
                      dest="window_size", default=-1,
                      help="window size for calculating rate, max size is 50000")

    channel_name = ""
    (options, args) = parser.parse_args(args)
    if len(args) == 0:
        parser.error("channelname must be specified")
    if len(args) == 1:
        channel_name = args[0]
    if len(args) > 1:
        parser.error("param is too much")

    try:
        if options.window_size != -1:
            import string
            window_size = string.atoi(options.window_size)
        else:
            window_size = options.window_size
    except:
        parser.error("window size must be an integer")

    channel_bw(channel_name, window_size)


class CyberChannelHz(object):

    """
    CyberChannelHz receives messages for a topic and computes frequency stats
    """

    def __init__(self, window_size):
        import threading
        self.lock = threading.Lock()
        self.last_printed_tn = 0
        self.msg_t0 = -1.
        self.msg_tn = 0
        self.times = []

        if window_size <= 0 or window_size > 50000:
            window_size = 50000
        self.window_size = window_size
        print("hz window_size: ", window_size)

    def callback_hz(self, m):
        with self.lock:
            curr_time = cyber_time.Time.now().to_sec()

            if curr_time == 0:
                if len(self.times) > 0:
                    print("reset times.")
                    self.times = []
                return

            if self.msg_t0 < 0 or self.msg_t0 > curr_time:
                self.msg_t0 = curr_time
                self.msg_tn = curr_time
                self.times = []
            else:
                self.times.append(curr_time - self.msg_tn)
                self.msg_tn = curr_time

            if len(self.times) > self.window_size - 1:
                self.times.pop(0)

    def print_hz(self):
        """
        print the average publishing rate to screen
        """
        if not self.times:
            return
        elif self.msg_tn == self.last_printed_tn:
            print("no new messages")
            return
        with self.lock:
            n = len(self.times)
            mean = sum(self.times) / n
            rate = 1. / mean if mean > 0. else 0

            std_dev = math.sqrt(sum((x - mean) ** 2 for x in self.times) / n)

            max_delta = max(self.times)
            min_delta = min(self.times)

            self.last_printed_tn = self.msg_tn
        print("average rate: %.3f\n\tmin: %.3fs max: %.3fs std dev: %.5fs window: %s" %
              (rate, min_delta, max_delta, std_dev, n + 1))


def channel_hz(channel_name, window_size):
    rt = CyberChannelHz(window_size)
    node_hz = cyber.Node("listener_node_hz")
    node_hz.create_rawdata_reader(channel_name, rt.callback_hz)
    print("reader to [%s]" % channel_name)
    while not cyber.is_shutdown():
        time.sleep(1.0)
        rt.print_hz()


def _channel_cmd_hz(argv):
    """
    Command-line parsing for 'cyber_channel hz' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel hz channelname")
    parser.add_option("-w", "--window",
                      dest="window_size", default=-1,
                      help="window size for calculating rate, max size is 50000")

    channel_name = ""
    (options, args) = parser.parse_args(args)
    if len(args) == 0:
        parser.error("channelname must be specified")
    if len(args) == 1:
        channel_name = args[0]
    if len(args) > 1:
        parser.error("param is too much")

    # check string
    try:
        if options.window_size != -1:
            import string
            window_size = string.atoi(options.window_size)
        else:
            window_size = options.window_size
    except:
        parser.error("window size must be an integer")

    channel_hz(channel_name, window_size)


def print_role(rolsattr_rawdata):
    from google.protobuf.message import DecodeError
    from cyber.proto.role_attributes_pb2 import RoleAttributes
    try:
        msg = RoleAttributes()
        msg.ParseFromString(rolsattr_rawdata)
    except DecodeError:
        print("RoleAttributes ParseFromString failed. size is ", len(rolsattr_rawdata))
        return
    print("\troleid\t\t", msg.id)
    print("\thostname\t", msg.host_name)
    print("\tprocessid\t", msg.process_id)
    print("\tnodename\t", msg.node_name)
    print("\tmsgtype\t\t", msg.message_type)


def channel_info(channel_name):
    channlesinfo_dict = cyber.ChannelUtils.get_channels_info()
    time.sleep(1)
    if len(channlesinfo_dict) == 0:
        print("channelsinfo dict is null")
        return

    # for key in channlesinfo_dict.keys():
    #     print key
    if channel_name != "":
        print(channel_name)
        for role_data in channlesinfo_dict[channel_name]:
            print_role(role_data)
    else:
        channels = sorted(channlesinfo_dict.keys())
        print("The number of channels is: ", len(channels))
        for channel in channels:
            print(channel)
            for role_data in channlesinfo_dict[channel]:
                print_role(role_data)


def _channel_cmd_info(argv):
    """
    Command-line parsing for 'cyber_channel info' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel info channelname ")
    parser.add_option("-a", "--all",
                      dest="all_channels", default=False,
                      action="store_true",
                      help="display all channels info")

    (options, args) = parser.parse_args(args)
    if len(args) == 0 and not options.all_channels:
        parser.error("channelname must be specified")
    elif len(args) > 1:
        parser.error("you may only specify one topic name")
    elif len(args) == 1:
        channel_info(args[0])
    elif len(args) == 0 and options.all_channels:
        channel_info("")


def print_channel_list():
    channels = sorted(cyber.ChannelUtils.get_channels())
    print("The number of channels is: ", len(channels))
    for channel in channels:
        print(channel)


def _channel_cmd_list(argv):
    """
    Command-line parsing for 'cyber_channel list' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel list")
    (options, args) = parser.parse_args(args)
    if len(args) > 0:
        parser.error("param is too much")
    print_channel_list()


class CyberChannelecho(object):

    def __init__(self, channel_name):
        self.channel_name = channel_name

    def callback(self, raw_data):
        """
        Channel echo callback.
        """
        # pass
        # print "py:reader callback raw_data->:"
        # print type(raw_data) # str
        # print raw_data # str

        msgtype = cyber.ChannelUtils.get_msgtype(self.channel_name, 0).decode('utf-8')
        print(cyber.ChannelUtils.get_debugstring_rawmsgdata(msgtype, raw_data).decode('utf-8'))


def channel_echo(channel_name):
    """
    Reader message.
    """
    node_echo = cyber.Node("listener_node_echo")
    echo_cb = CyberChannelecho(channel_name)
    node_echo.create_rawdata_reader(channel_name, echo_cb.callback)
    while not cyber.is_shutdown():
        pass


def _channel_cmd_echo(argv):
    """
    Command-line parsing for 'cyber_channel echo' command.
    """
    args = argv[2:]
    from optparse import OptionParser
    parser = OptionParser(
        usage="usage: cyber_channel echo channelname")
    (options, args) = parser.parse_args(args)
    if len(args) > 1:
        parser.error("you may only specify one input channel")
    elif len(args) == 0:
        parser.error("channelname must be specified")
    channel_echo(args[0])


def _printallusage():
    print("""cyber_channel is a command-line tool for printing information about CyberRT Channels.

Commands:
\tcyber_channel list\tlist active channels
\tcyber_channel info\tprint information about active channel
\tcyber_channel echo\tprint messages to screen
\tcyber_channel hz\tdisplay publishing rate of channel
\tcyber_channel bw\tdisplay bandwidth used by channel
\tcyber_channel type\tprint channel type

Type cyber_channel <command> -h for more detailed usage, e.g. 'cyber_channel echo -h'
""")
    sys.exit(getattr(os, 'EX_USAGE', 1))


if __name__ == '__main__':
    if len(sys.argv) == 1:
        _printallusage()

    cyber.init()

    argv = sys.argv[0:]
    command = argv[1]
    if command == 'list':
        _channel_cmd_list(argv)
    elif command == 'info':
        _channel_cmd_info(argv)
    elif command == 'echo':
        _channel_cmd_echo(argv)
    elif command == 'hz':
        _channel_cmd_hz(argv)
    elif command == 'bw':
        _channel_cmd_bw(argv)
    elif command == 'type':
        _channel_cmd_type(argv)
    else:
        _printallusage()

    cyber.shutdown()
