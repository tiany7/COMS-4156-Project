package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "person_client",
    srcs = ["person_client.cpp"],
    deps = ["@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "//proto/person_proto:person_cc_grpc",
            "//services/authentication_service:auth_lib",
            "@json_lib//:json",
            "@comm_github_mysql_cpp_connector//:mysql_lib",],
    linkopts = ["-lpthread"],
)
