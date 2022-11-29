cc_library(
    name = "random_generator",
    srcs = ["random_generator.cpp"],
    hdrs = ["random_generator.h"],
)

cc_binary(
    name = "auth_main",
    srcs = ["auth_main.cpp"],
    deps = [":random_generator"],
)

cc_test(
    name = "random_generator_test",
    srcs = ["random_generator_test.cpp"],
    deps = [":random_generator",
            "@com_google_googletest//:gtest_main",],
)

cc_library(
    name = "redis_client",
    srcs = ["redis_client.cpp"],
    hdrs = ["redis_client.h"],
    linkopts = ["-lpthread"],
    deps = ["@redis_lib//:cpp_redis"],
)

cc_test(
    name = "redis_client_test",
    srcs = ["redis_client_test.cpp"],
    deps = [":redis_client",
            "@com_google_googletest//:gtest_main",],
)

cc_library(
    name = "login",
    srcs = ["login.cpp"],
    hdrs = ["login.h"],
    deps = [":redis_client",
            ":random_generator"],
)

cc_test(
    name = "login_test",
    srcs = ["login_test.cpp"],
    deps = [":login",
            "@com_google_googletest//:gtest_main",],
)

cc_binary(
    name = "http_server",
    srcs = ["http_layer.cpp"],
    defines= ["CPPHTTPLIB_OPENSSL_SUPPORT"],
    visibility = ["//visibility:public"],
    deps = ["@comm_github_mysql_cpp_connector//:mysql_lib",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@json_lib//:json",
            ":login"],
    linkopts = ["-lpthread"],
)

cc_binary(
    name = "auth_server",
    srcs = ["auth_service.cpp"],
    visibility = ["//visibility:public"],
    deps = ["@com_github_grpc_grpc//:grpc++_reflection",
            "@com_github_grpc_grpc//:grpc++",
            "//proto/authentication_proto:auth_cc_grpc",
            ":login"],
)


package(default_visibility = ["//visibility:public"])
cc_library(
    name = "auth_lib",
    hdrs = ["auth_checker.h"],
    deps = [":login",
            "//proto/authentication_proto:auth_cc_grpc",
            "@com_github_grpc_grpc//:grpc++_reflection",
            "@com_github_grpc_grpc//:grpc++",
            ],
)
cc_binary(
    name = "auth_client",
    srcs = ["client_main.cpp"],
    deps = [":auth_lib"],
    copts = ["-std=c++17"],
)