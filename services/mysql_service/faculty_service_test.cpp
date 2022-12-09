#include "faculty_service.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
using grpc::Channel;
using grpc::ClientContext;
using namespace testing;


class MockFacultyDBService : public FacultyDBService{
public:

    MOCK_METHOD2(GetFacultyDept, int( std::string,FacultyRsp*));
    MOCK_METHOD2(GetFacultyUni, int( std::string,FacultyRsp*));
    MOCK_METHOD4(InsertFaculty, int(std::string, std::string, std::string, std::string));
    MOCK_METHOD2(CalculateSomething, int(int ,int));
    MOCK_METHOD0(Print, int());

};


TEST(HelloTest, PP) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// TEST(TestMySQLServer, Initialize){
//     FacultyDBService mock;
//     FacultyRsp rsp;
// //    EXPECT_CALL(mock, GetFacultyDept("test", &rsp)).Times(1).WillOnce(Return(1));
//     auto res = mock.GetFacultyDept("COMS", &rsp);
//     EXPECT_EQ(0, res);
// }

// TEST(TestMySQLServer, Initialize2){
//     FacultyDBService mock;
//     int res = mock.CalculateSomething(1,2);
//     EXPECT_EQ(3, res);
// }

// TEST(TestMySQLServer, Initialize3){
//     FacultyDBService mock;
//     FacultyRsp rsp;
//     EXPECT_EQ(1, mock.Print());

// }

TEST(ProfpostTest, Create){
    FacultyDBService mock;
    auto res = mock.InsertPost("fg1121", "Hello world!", "Active", "20221122151515fg1121");
    EXPECT_EQ(0, res);
}

TEST(ProfpostTest, Read){
    FacultyDBService mock;
    ProfpostRsp reply;
    auto res = mock.GetPost("fg1121", &reply);
    EXPECT_EQ(0, res);
}

TEST(ProfpostTest, Update){
    FacultyDBService mock;
    auto res = mock.InsertPost("fg1121", "New Content", "Active", "20221122151515fg1121");
    EXPECT_EQ(0, res);
}

TEST(ProfpostTest, Delete){
    FacultyDBService mock;
    auto res = mock.DelPost("20221122151515fg1121");
    EXPECT_EQ(0, res);
}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
//    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}