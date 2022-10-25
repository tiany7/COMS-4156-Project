cc_binary(
    name = "course_service",
    srcs = [
        "course_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = [":course_lib"],
)

cc_library(
    name = "course_lib",
    hdrs = ["course_service.h"],
    srcs = ["course_service.cpp"],
    visibility = ["//visibility:public"],
        deps = ["//proto/course_proto:course_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@com_github_grpc_grpc//:grpc++_reflection"],
        linkopts = ["-I/usr/include/",
                "-I/usr/include/cppconn",
                "-L/usr/lib",
                "-L/usr/local/lib64",
                "-lmysqlcppconn",],
        copts = ["-std=c++17"],
)

cc_test(
  name = "course_service_test",
  size = "small",
  srcs = ["course_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          ":course_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)