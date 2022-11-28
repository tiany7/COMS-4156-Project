load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "auth_proto",
    srcs = ["login.proto",],
)

cc_proto_library(
    name = "auth_cc_proto",
    deps = [":auth_proto",],
)

cc_grpc_library(
    name = "auth_cc_grpc",
    srcs = [":auth_proto"],
    grpc_only = True,
    generate_mocks = True,
    deps = [":auth_cc_proto"],
    visibility = ["//visibility:public"]
)