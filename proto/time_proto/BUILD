load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "time_proto",
    srcs = ["time.proto",],
)

cc_proto_library(
    name = "time_cc_proto",
    deps = [":time_proto",],
)

cc_grpc_library(
    name = "time_cc_grpc",
    srcs = [":time_proto"],
    grpc_only = True,
    generate_mocks = True,
    deps = [":time_cc_proto"],
    visibility = ["//visibility:public"]
)