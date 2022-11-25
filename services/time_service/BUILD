cc_binary(
    name = "rippled",
    srcs = [
        "time_service.cc"
    ],
    visibility = ["//visibility:public"],
    deps = ["//proto/time_proto:time_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-lmysqlcppconn",],
    copts = ["-std=c++20"],
)

cc_library(
    name = "db_service",
    srcs = ["DB.cc"],
    hdrs = ["DB.hh"],
    deps = ["@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-lmysqlcppconn",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "time_db_service",
    hdrs = ["time_service.hh"],
    srcs = ["time_service.cc"],
    deps = ["//proto/time_proto:time_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@com_github_grpc_grpc//:grpc++_reflection",
                "@comm_github_mysql_cpp_connector//:mysql_lib",
                ":db_service"],
    linkopts = ["-lmysqlcppconn",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mysql_server",
    srcs = ["mysql_server.cc"],
    hdrs = ["mysql_server.hh"],
    deps = ["//proto/time_proto:time_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib",
            ":time_db_service"],
)

cc_binary(
    name = "db_server",
    srcs = ["db_service_main.cc"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    deps = [":mysql_server",
            "@comm_github_mysql_cpp_connector//:httplib"],
    linkopts = ["-lpthread"],
)

cc_test(
  name = "time_service_test",
  size = "small",
  srcs = ["time_service_test.cc"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/time_proto:time_cc_grpc",
          ":time_db_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
)