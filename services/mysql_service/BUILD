cc_binary(
    name = "rippled",
    srcs = [
        "faculty_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-L/usr/lib/mysql",
            "-lmysqlcppconn",],
    copts = ["-std=c++17"],
)

cc_test(
  name = "hello_test",
  size = "small",
  srcs = ["faculty_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main"],
)