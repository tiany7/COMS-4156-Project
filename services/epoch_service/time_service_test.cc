#include "time_service.hh"

#include <gtest/gtest.h>

using grpc::Channel;
using grpc::ClientContext;
using namespace testing;

TEST(TimeTest, BasicAssertions) {
    TimeDB tdb;
    tdb.addAppt("2022-10-10 08:00:00", "2022-10-20 20:00:00");
    EXPECT_EQ(tdb.checkTime(), false);
    tdb.addAppt("2022-10-21 08:00:00", "2023-11-30 20:00:00");
    EXPECT_EQ(tdb.checkTime(), true);
    tdb.resetAppt();
    EXPECT_EQ(tdb.checkTime(), false);
}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}