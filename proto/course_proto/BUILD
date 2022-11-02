package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

proto_library(
    name = "course_proto",
    srcs = ["course.proto",],
)

cc_proto_library(
    name = "course_cc_proto",
    deps = [":course_proto",],
)

cc_grpc_library(
    name = "course_cc_grpc",
    srcs = [":course_proto"],
    grpc_only = True,
    generate_mocks = True,
    deps = [":course_cc_proto"],
)
