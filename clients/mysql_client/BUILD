package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "sql_client",
    srcs = ["mysql_client.cpp"],
    deps = ["@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "//proto/mysql_server_proto:faculty_cc_grpc"],
    copts = ["-std=c++17"],
)