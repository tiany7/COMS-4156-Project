#include "auth_checker.h"

using namespace std;

int main(int argc, char *argv[])
{
    AuthServiceClient auth_checker(
            grpc::CreateChannel("localhost:95955", grpc::InsecureChannelCredentials()));;
    cout<<auth_checker.CheckSecret("test", "test")<<endl;
    cout<<auth_checker.IsLoggedIn("Yuanhan")<<endl;

    return 0;
}