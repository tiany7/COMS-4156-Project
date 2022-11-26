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
    linkopts = [ "-lmysqlcppconn",
                 "-I/usr/include/",],
    copts = ["-std=c++17"],
)

cc_library(
    name = "db_service",
    srcs = ["DB.cpp"],
    hdrs = ["DB.h"],
    deps = ["@comm_github_mysql_cpp_connector//:mysql_lib"],
    linkopts = ["-I/usr/include/",
                "-lmysqlcppconn",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "faculty_db_service",
    hdrs = ["faculty_service.h"],
    srcs = ["faculty_service.cpp"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
                "@com_github_grpc_grpc//:grpc++",
                "@com_github_grpc_grpc//:grpc++_reflection",
                "@comm_github_mysql_cpp_connector//:mysql_lib",
                ":db_service"],
    linkopts = ["-I/usr/include/",
                "-lmysqlcppconn",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mysql_server",
    srcs = ["mysql_server.cpp"],
    hdrs = ["mysql_server.h"],
    deps = ["//proto/mysql_server_proto:faculty_cc_grpc",
            "@com_github_grpc_grpc//:grpc++",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@comm_github_mysql_cpp_connector//:mysql_lib",
            ":faculty_db_service"],
)

cc_binary(
    name = "db_server",
    srcs = ["db_service_main.cpp"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    deps = [":mysql_server",
            "@comm_github_mysql_cpp_connector//:httplib"],
    linkopts = ["-lpthread"],
)

cc_test(
    name = "faculty_db_service_test",
    srcs = ["faculty_service_test.cpp"],
    deps = [":faculty_db_service",
            "@com_google_googletest//:gtest_main",],
    defines = ["TESTING"],
)
cc_test(
  name = "faculty_service_test",
  size = "small",
  srcs = ["mysql_server_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "//proto/mysql_server_proto:faculty_cc_grpc",
          ":faculty_db_service",
          "@com_github_grpc_grpc//:grpc++",
          "@com_github_grpc_grpc//:grpc++_reflection",],
  defines= ["TESTING"],
  linkopts = ["-Dgtest_disable_pthreads=OFF"],
)