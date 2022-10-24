cc_binary(
    name = "am_service",
    srcs = [
        "am_service.cpp"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/am_proto:am_cc_grpc",
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
  name = "am_service_test",
  size = "small",
  srcs = ["am_service_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/am_proto:am_cc_grpc",
          ":am_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)