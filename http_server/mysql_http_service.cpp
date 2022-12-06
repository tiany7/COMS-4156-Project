#include "mysql_http_service.h"



vector<Faculty> FacultyServiceClient::GetFaculty(string dept) {
    GetFacultyReq request;
    request.set_department(dept);

    FacultyRsp reply;

    ClientContext context;

    Status status = stub_->GetFaculty(&context, request, &reply);

    if (status.ok()) {
        vector<Faculty>v;
        for(auto it : *reply.mutable_faculty()){
            v.push_back(it);
        }
        return v;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return {};
    }
}

vector<Faculty> FacultyServiceClient::GetFacultyByUni(const string &uni) {
    GetFacultyReq request;
    request.set_uni(uni);

    FacultyRsp reply;

    ClientContext context;
    Status status = stub_->GetFacultyByUni(&context, request, &reply);

    if (status.ok()) {
        vector<Faculty>v;
        for(auto it : *reply.mutable_faculty()){
            v.push_back(it);
        }
        return v;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return {};
    }
}

vector<Profpost> FacultyServiceClient::GetPost(const string &uni) {
    GetPostReq request;
    request.set_uni(uni);

    ProfpostRsp reply;

    ClientContext context;
    Status status = stub_->GetPost(&context, request, &reply);

    if (status.ok()) {
        vector<Profpost> v;
        for(auto it : *reply.mutable_profpost()){
            v.push_back(it);
        }
        return v;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return {};
    }
}

int FacultyServiceClient::InsertFaculty(const string &name, const string &dept, const string &uni, const string & country) {
    Faculty f;
    f.set_name(name);
    f.set_department(dept);
    f.set_uni(uni);
    f.set_country(country);

    Faculty reply;

    ClientContext context;

    Status status = stub_->InsertFaculty(&context, f, &reply);

    if (status.ok()) {
        return 0;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return -1;
    }
}

int FacultyServiceClient::InsertPost(const string &uni, const string &content, const string &status, const string & postid) {
    Profpost f;
    f.set_uni(uni);
    f.set_content(content);
    f.set_status(status);
    f.set_postid(postid);

    Profpost reply;

    ClientContext context;

    auto ret = stub_->InsertPost(&context, f, &reply);

    if (ret.ok()) {
        return 0;
    } else {
        std::cout << ret.error_code() << ": " << ret.error_message()
                    << std::endl;
        return -1;
    }
}

int FacultyServiceClient::ModifyPost(const string & postid, const string &uni, const string &content, const string &status){
    return InsertPost(uni, content, status, postid);
}

int FacultyServiceClient::DeletePost(const string & postid) {
    DelPostReq f;
    f.set_postid(postid);

    Profpost reply;

    ClientContext context;

    Status status = stub_->DelPost(&context, f, &reply);

    if (status.ok()) {
        return 0;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return -1;
    }
}


int main(int argc, char** argv) {
    FacultyServiceClient facultyServiceClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    httplib::Server svr;
    AuthServiceClient auth_checker(
            grpc::CreateChannel("localhost:95955", grpc::InsecureChannelCredentials()));

    svr.Options("/(.*)",
              [&](const httplib::Request & /*req*/, httplib::Response &res) {
                  res.set_header("Access-Control-Allow-Methods", " POST, GET, OPTIONS");
                  res.set_header("Content-Type", "text/html; charset=utf-8");
                  res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept");
                  res.set_header("Access-Control-Allow-Origin", "*");
                  res.set_header("Connection", "close");
              });
    
    svr.Get("/search_dept", [&](const httplib::Request & req, httplib::Response &res) {
        auto param = req.get_param_value("department");
        vector<Faculty> v = facultyServiceClient.GetFaculty(param);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    svr.Get("/search_uni", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("uni");
        vector<Faculty> v = facultyServiceClient.GetFacultyByUni(body);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    svr.Post("/add_instructor", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto name = js["name"];
        auto dept = js["department"];
        auto uni = js["uni"];
        auto country = js["country"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.InsertFaculty(name, dept, uni, country);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Post("/add_profpost", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto uni = js["uni"];
        auto content = js["content"];
        auto status = js["status"];
        auto postid = js["postid"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.InsertPost(uni, content, status, postid);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Post("/mod_profpost", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto uni = js["uni"];
        auto content = js["content"];
        auto status = js["status"];
        auto postid = js["postid"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.ModifyPost(postid, uni, content, status);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Get("/search_post", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("uni");
        auto v = facultyServiceClient.GetPost(body);
        std::ostringstream os;
        for(auto it : v){
            os << it.postid()<<" | "<< it.uni()<< " | "<<it.content()<<" | "<<it.status()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}