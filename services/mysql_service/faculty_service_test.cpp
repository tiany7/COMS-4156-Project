#include "faculty_service.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
using grpc::Channel;
using grpc::ClientContext;
using namespace testing;
TEST(HelloTest, PP) {
// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}



class MockFacultyDBService : public FacultyDBService{
public:

    MOCK_METHOD2(GetFacultyDept, int( std::string,FacultyRsp*));
    MOCK_METHOD2(GetFacultyUni, int( std::string,FacultyRsp*));
    MOCK_METHOD4(InsertFaculty, int(std::string, std::string, std::string, std::string));
    MOCK_METHOD2(CalculateSomething, int(int ,int));
    MOCK_METHOD0(Print, int());

};

//TEST(TestMySQLServer, Initialize){
//    MockFacultyDBService mock;
//    FacultyRsp rsp;
//    EXPECT_CALL(mock, GetFacultyDept("test", &rsp)).Times(1).WillOnce(Return(1));
//    EXPECT_EQ(1, mock.GetFacultyDept("test", &rsp));
//
//}

TEST(TestMySQLServer, Initialize2){
    FacultyDBService mock;
    int res = mock.CalculateSomething(1,2);
    EXPECT_EQ(3, res);
}

TEST(TestMySQLServer, Initialize3){
    FacultyDBService mock;
    FacultyRsp rsp;
    EXPECT_EQ(1, mock.Print());

}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
//    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}