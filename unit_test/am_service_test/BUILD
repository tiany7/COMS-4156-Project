cc_test(
  name = "am_service_test",
  size = "small",
  srcs = ["am_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/am_proto:am_cc_grpc",
          "//services/am_service:am_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)