cc_binary(
    name = "db_init_tables",
    srcs = ["init_mysql.cc"],
    deps = ["@comm_github_mysql_cpp_connector//:mysql_lib",],
    linkopts = ["-lmysqlcppconn",],
    visibility = ["//visibility:public"],
)