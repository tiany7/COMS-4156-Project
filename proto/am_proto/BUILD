load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "am_proto",
    srcs = ["am.proto",],
)

cc_proto_library(
    name = "am_cc_proto",
    deps = [":am_proto",],
)

cc_grpc_library(
    name = "am_cc_grpc",
    srcs = [":am_proto"],
    grpc_only = True,
    deps = [":am_cc_proto"],
    visibility = ["//visibility:public"]
)