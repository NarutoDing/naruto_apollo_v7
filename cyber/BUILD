load("@rules_cc//cc:defs.bzl", "cc_library")
load("//tools/install:install.bzl", "install", "install_files")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cyber",
    linkstatic = False,
    deps = [
        ":cyber_core",
    ],
)

install(
    name = "install",
    data = [
        ":.release.bash",
        ":cyber_conf",
        "//cyber/python/cyber_py3:runtime_files",
    ],
    rename = {
        "cyber/.release.bash": "setup.bash",
    },
    deps = [
        ":pb_cyber",
        "//cyber/mainboard:install",
        "//cyber/python/internal:install",
        "//cyber/tools:install",
    ],
)

install_files(
    name = "pb_cyber",
    dest = "cyber",
    files = [
        "//cyber/proto:record_py_pb2",
    ],
)

cc_library(
    name = "binary",
    srcs = ["binary.cc"],
    hdrs = ["binary.h"],
)

cc_library(
    name = "state",
    srcs = ["state.cc"],
    hdrs = ["state.h"],
    deps = [
        "//cyber/common",
    ],
)

cc_library(
    name = "init",
    srcs = ["init.cc"],
    hdrs = ["init.h"],
    deps = [
        "//cyber:binary",
        "//cyber:state",
        "//cyber/common:file",
        "//cyber/logger:async_logger",
        "//cyber/node",
        "//cyber/proto:clock_cc_proto",
        "//cyber/sysmo",
        "//cyber/time:clock",
        "//cyber/timer:timing_wheel",
    ],
)

cc_library(
    name = "cyber_core",
    srcs = ["cyber.cc"],
    hdrs = ["cyber.h"],
    linkopts = ["-lrt"],
    deps = [
        "//cyber:binary",
        "//cyber:init",
        "//cyber:state",
        "//cyber/base",
        "//cyber/blocker:blocker_manager",
        "//cyber/class_loader",
        "//cyber/class_loader:class_loader_manager",
        "//cyber/common",
        "//cyber/component",
        "//cyber/component:timer_component",
        "//cyber/croutine",
        "//cyber/data",
        "//cyber/event:perf_event_cache",
        "//cyber/io",
        "//cyber/logger",
        "//cyber/logger:async_logger",
        "//cyber/message:message_traits",
        "//cyber/message:protobuf_traits",
        "//cyber/message:py_message_traits",
        "//cyber/message:raw_message_traits",
        "//cyber/node",
        "//cyber/parameter:parameter_client",
        "//cyber/parameter:parameter_server",
        "//cyber/proto:run_mode_conf_cc_proto",
        "//cyber/record",
        "//cyber/scheduler",
        "//cyber/scheduler:scheduler_factory",
        "//cyber/service",
        "//cyber/service:client",
        "//cyber/service_discovery:topology_manager",
        "//cyber/sysmo",
        "//cyber/task",
        "//cyber/time",
        "//cyber/time:clock",
        "//cyber/time:duration",
        "//cyber/time:rate",
        "//cyber/timer",
        "//cyber/transport",
        "//cyber/transport/rtps:participant",
        "//cyber/transport/rtps:sub_listener",
        "@com_github_google_glog//:glog",
        "@com_google_protobuf//:protobuf",
        "@fastrtps",
    ],
)

filegroup(
    name = "cyber_conf",
    srcs = glob([
        "conf/*.conf",
    ]),
)

cpplint()
