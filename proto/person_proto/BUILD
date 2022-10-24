package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "person_proto",
    srcs = ["person.proto",],
)

cc_proto_library(
    name = "person_cc_proto",
    deps = [":person_proto",],
)

cc_grpc_library(
    name = "person_cc_grpc",
    srcs = [":person_proto"],
    grpc_only = True,
    generate_mocks = True,
    deps = [":person_cc_proto"],
)