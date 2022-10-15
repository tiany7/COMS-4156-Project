#include "gtest/gtest.h"

using echo::EchoRequest;
using echo::EchoResponse;

TEST(EchoTest, EchoService) {
    EchoRequest* request;
    request->set_message("world!");
}

