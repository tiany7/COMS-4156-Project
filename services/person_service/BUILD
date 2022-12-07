cc_binary(
    name = "person_service",
    srcs = [
        "person_service.cpp",
        "person_service.h",
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/person_proto:person_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-lmysqlcppconn",],
    copts = ["-std=c++17"],
)

cc_test(
  name = "person_service_test",
  size = "small",
  srcs = ["person_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/person_proto:person_cc_grpc",
          "//services/person_service:person_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)
