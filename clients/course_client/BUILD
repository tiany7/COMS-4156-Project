package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "course_client",
    srcs = ["course_client.cpp"],
    deps = ["@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "//proto/course_proto:course_cc_grpc",
            "@comm_github_mysql_cpp_connector//:mysql_lib",],
    linkopts = ["-lpthread"],
    copts = ["-std=c++17"],
)
