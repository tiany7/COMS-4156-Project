cc_binary(
    name = "rippled",
    srcs = [
        "faculty_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection"],
    linkopts = ["-I/usr/include/",
            "-I/usr/include/cppconn",
            "-L/usr/lib",
            "-lmysqlcppconn",],
    copts = ["-std=c++17"],
)