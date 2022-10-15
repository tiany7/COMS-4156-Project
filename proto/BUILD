load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "echo_proto",
    srcs = ["echo.proto",],
)

cc_proto_library(
    name = "echo_cc_proto",
    deps = ["//proto:echo_proto",],
)

cc_grpc_library(
    name = "echo_cc_grpc",
    srcs = ["//proto:echo_proto"],
    grpc_only = True,
    deps = ["//proto:echo_cc_proto"],
    visibility = ["//visibility:public"]
)