#include "login_operator.h"
#include "redis_instance.h"
#include "r3c/r3c.h"
using namespace r3c;

login_operator::login_operator(string &uid, string &ss, string &bev)
    : user_id(std::move(uid)), session(std::move(ss)), bevstring(std::move(bev))
{

}

string login_operator::handler()
{
    CRedisClient *rds = redis_instance::getInstance();

    //出错返回值
    Json json = Json::object({{"action","login"}, {"msg","服务器错误"},
                              {"status","error"}, {"bev", bevstring}});
    string result_json = json.dump();

    string key = "status:"+user_id;
    string status;
    try{
        rds->hget(key, "status", &status);
        if(status.empty())
            rds->hset(key, "status", "online");

        rds->hset(key, "user_id", user_id);
        rds->hset(key, "session", session);
    }
    catch(CRedisException &e){
        rds->del(key);
        cout << "login_operator err:" << e.what() << "\n";
        return result_json;
    }

    //正常登录,
    if(status.empty())
        return "";

    if(status != "gaming")
         return "";

    //逃跑&掉线
    json = Json::object({{"action", "login"},{"msg","您有一局游戏还没有结束"},
                        {"status", "inform"},{"bev", bevstring}});
    return json.dump();
}
