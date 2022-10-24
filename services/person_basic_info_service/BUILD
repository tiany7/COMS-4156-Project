cc_binary(
    name = "person_service",
    srcs = [
        "person_service.cpp",
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/person_proto:person_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-L/usr/local/mysql/lib",
                "-lmysqlcppconn",],
    copts = ["-std=c++17"],
)


