#!/usr/bin/env python3

###############################################################################
# Copyright 2018 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

from modules.common.proto import error_code_pb2
from modules.tools.record_analyzer.common.statistical_analyzer import PrintColors
from modules.tools.record_analyzer.common.distribution_analyzer import DistributionAnalyzer


class ErrorMsgAnalyzer:
    """class"""

    def __init__(self):
        """init"""
        self.error_msg_count = {}

    def put(self, error_msg):
        """put"""
        if len(error_msg) == 0:
            return
        if error_msg not in self.error_msg_count:
            self.error_msg_count[error_msg] = 1
        else:
            self.error_msg_count[error_msg] += 1

    def print_results(self):
        """print"""
        DistributionAnalyzer().print_distribution_results(self.error_msg_count)
