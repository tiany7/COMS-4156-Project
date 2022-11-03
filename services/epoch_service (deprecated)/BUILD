package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "echo_service",
    srcs = ["echo_service.cpp"],
    deps = ["//proto/echo_proto:echo_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection"],
)

cc_library(
    name = "time_service",
    srcs = ["time_service.cc"],
    hdrs = ["time_service.hh"],
    deps = ["//proto/echo_proto:time_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib"],
    copts = ["-std=c++20"],
)

cc_test(
  name = "time_service_test",
  size = "small",
  srcs = ["time_service_test.cc"],
  deps = ["@com_google_googletest//:gtest_main",
          ":time_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)