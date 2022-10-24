cc_binary(
    name = "course_service",
    srcs = [
        "course_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/course_proto:course_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection"],
    linkopts = ["-I/usr/include/",
            "-I/usr/include/cppconn",
            "-L/usr/lib",
            "-L/usr/local/lib64",
            "-lmysqlcppconn",],
    copts = ["-std=c++17"],
)
