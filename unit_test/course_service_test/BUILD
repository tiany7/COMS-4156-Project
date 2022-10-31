cc_test(
  name = "course_service_test",
  size = "small",
  srcs = ["course_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/course_proto:course_cc_grpc",
          "//services/course_service:course_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)

