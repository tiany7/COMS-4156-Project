#include "login.h"

Login::Login()
{
    redis_client_ = new RedisClient();
    redis_client_->Connect();
    random_generator_ = new RandomGenerator();

}

Login::~Login()
{
    if(redis_client_)delete redis_client_;
}


std::string Login::getRedisKey(const std::string &username)
{
    return "user:" + username;
}

bool Login::Register(const std::string& username, const std::string& password)
{
    if (redis_client_->Exists(getRedisKey(username)))
    {
        std::cout<<"user already exists"<<std::endl;
        return false;
    }
    redis_client_->Set(username, password);
    redis_client_->Commit();
    return true;
}

std::string Login::getRedisLogKey(const std::string& username)
{
    return "log:" + username;
}

std::string Login::LogIn(const std::string& username, const std::string& password)
{
    auto key = getRedisKey(username);
    auto logKey =getRedisLogKey(username);
    if (!redis_client_->Exists(username))
    {
        return "user not exists";
    }
    try{
        if (redis_client_->CompareIfEqual(logKey, "true"))
        {
            return "Already logged in";
        }
    }catch(cpp_redis::redis_error& e){
        std::cout << e.what() << std::endl;
    }
    redis_client_->Set(logKey, "true");
    if (redis_client_->CompareIfEqual(username, password))
    {
        auto token = random_generator_->GenerateToken(username);
        redis_client_->Set(key, token);
        redis_client_->Commit();
        return token;
    }
    return "";
}


void Login::LogOut(const std::string& username)
{
    auto logKey =getRedisLogKey(username);
    redis_client_->Set(logKey, "false");
    redis_client_->Commit();
}

bool Login::IsLoggedIn(const std::string& username)
{
    auto logKey =getRedisLogKey(username);
    return redis_client_->CompareIfEqual(logKey, "true");
}

bool Login::IsLegalOperator(const std::string& username, const std::string& secret)
{
    auto key = getRedisKey(username);
    return redis_client_->CompareIfEqual(key, secret);
}

