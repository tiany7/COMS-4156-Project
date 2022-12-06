workspace(name = "coms4156_project")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/16f637fbf4ffc3f7a01fa4eceb7906634565242f.zip"],
    strip_prefix = "googletest-16f637fbf4ffc3f7a01fa4eceb7906634565242f",
    sha256 = "002d540f947e5981f54ddaab476d87b113d2a14822f21a34dca30f24c9492a24",
    )

http_archive(
    name = "com_google_protobuf",
    sha256 = "3bd7828aa5af4b13b99c191e8b1e884ebfa9ad371b0ce264605d347f135d2568",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.19.4.tar.gz"],
    strip_prefix = "protobuf-3.19.4",
    )

http_archive(
    name = "com_github_grpc_grpc",
    urls = ["https://github.com/grpc/grpc/archive/44c40ac23023b7b3dd82744372c06817cc203898.tar.gz",],
    strip_prefix = "grpc-44c40ac23023b7b3dd82744372c06817cc203898",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

load('@bazel_tools//tools/build_defs/repo:git.bzl', 'git_repository')
git_repository(
    name = "comm_github_mysql_cpp_connector",
    remote = "https://github.com/tiany7/mysql_dependencies.git",
    commit = "8ba122f93a2f5f9755d4fcef14fe9bcb6acd4edc",
)

git_repository(
    name = "http_lib",
    remote = "https://github.com/yhirose/cpp-httplib.git",
    commit = "27cd4e6ffeca2c9978ec1df7de3d22b9303a71b4",
)

git_repository(
    name = "redis_lib",
    remote = "https://github.com/Cylix/cpp_redis.git",
    commit = "de0e2665ab2fb058f8dd378aac2462ddc053e119",
)
http_archive(
    name = "tacopie",
    sha256 = "bbdebecdb68d5f9eb64170217000daf844e0aee18b8c4d3dd373d07efd9f7316",
    strip_prefix = "tacopie-master",
    url = "https://github.com/cylix/tacopie/archive/master.zip",
)



git_repository(
    name = "json_lib",
    remote = "https://github.com/nlohmann/json.git",
    commit = "a3e6e26dc83a726b292f5be0492fcc408663ce55",
)