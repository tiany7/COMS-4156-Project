package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "am_client",
    srcs = ["am_client.cpp"],
    deps = ["@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "//proto/am_proto:am_cc_grpc"],
    copts = ["-std=c++17"],
)