package(default_visibility = ["//visibility:public"])
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("//bazel:grpc_build_system.bzl", "grpc_proto_library")
cc_proto_library(
    name = "echo_proto_lib",
    deps = [
        ":echo_proto",
    ],
)

proto_library(
    name = "echo_proto",
    srcs = ["echo.proto",],
)

cc_grpc_library(
    name = "echo_cc_grpc",
    srcs = [":echo_proto_lib"],
    grpc_only = True,
    deps = [":wwccproto"],
)