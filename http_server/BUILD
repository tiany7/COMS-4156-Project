cc_binary(
    name = "mysql_http_server",
    srcs = ["mysql_http_service.cpp"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    visibility = ["//visibility:public"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@com_github_grpc_grpc//:grpc++_reflection",
                "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-lpthread"],
)