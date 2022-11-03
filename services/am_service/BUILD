cc_binary(
    name = "am_service",
    srcs = [
        "am_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/am_proto:am_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection"],
    linkopts = ["-I/usr/include/",
            "-I/usr/include/cppconn",
            "-L/usr/lib",
            "-L/usr/local/lib64",
            "-lmysqlcppconn",],
    copts = ["-std=c++17"],
)

cc_binary(
    name = "am_http_service",
    srcs = ["am_http_service.cpp"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    visibility = ["//visibility:public"],
    deps = ["//proto/am_proto:am_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@comm_github_mysql_cpp_connector//:mysql_lib",
                "@com_github_grpc_grpc//:grpc++_reflection"],
    linkopts = ["-lpthread",],
)