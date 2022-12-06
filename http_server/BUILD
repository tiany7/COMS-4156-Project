cc_binary(
    name = "mysql_http_server",
    hdrs = ["mysql_http_service.h"],
    srcs = ["mysql_http_service.cpp"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    visibility = ["//visibility:public"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@com_github_grpc_grpc//:grpc++_reflection",
                "//services/authentication_service:auth_lib",
                "@json_lib//:json",
                "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-lpthread"],
)