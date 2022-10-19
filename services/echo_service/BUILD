package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "echo_service",
    srcs = ["echo_service.cpp"],
    deps = ["//proto/echo_proto:echo_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection"],
)