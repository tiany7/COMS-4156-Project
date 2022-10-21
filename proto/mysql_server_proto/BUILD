load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "faculty_proto",
    srcs = ["faculty.proto",],
)

cc_proto_library(
    name = "faculty_cc_proto",
    deps = [":faculty_proto",],
)

cc_grpc_library(
    name = "faculty_cc_grpc",
    srcs = [":faculty_proto"],
    grpc_only = True,
    deps = [":faculty_cc_proto"],
    visibility = ["//visibility:public"]
)