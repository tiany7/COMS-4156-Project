package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "echo_main",
    srcs = ["echo_service.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
            "//proto_messages/echo_proto:echo_cc_grpc",
            "//:grpc++_reflection",
            "//:grpc++",],
    copts = ["-std=c++17"],
)