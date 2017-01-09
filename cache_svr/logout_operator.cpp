#include "logout_operator.h"

#include "redis_instance.h"

logout_operator::logout_operator(string &uid, string &ss, string bev)
    : user_id(std::move(uid)), session(std::move(ss)), bev_string(std::move(bev))
{

}

string logout_operator::handler()
{
    CRedisClient *rds = redis_instance::getInstance();

    //出错返回值
    Json json = Json::object({{"action","login"}, {"msg","服务器错误"},
                              {"status","error"}, {"bev", bev_string}});
    string result_json = json.dump();

    string key = "status:"+user_id;
    string old_session;
    string status;
    try {
        rds->hget(key, "session", &old_session);
        if(old_session.empty())
            return result_json;

        if(old_session != session)
            return result_json;

        rds->hget(key, "status", &status);
        if(status != "gaming") {
            rds->del(key);
        }
        else {
            rds->hdel(key, "session");
            rds->hset(key, "status", string("leave"));// 挂机/托管
        }
    }
    catch(CRedisException &e){
        cout << "logout_operator::handler err:" << e.what() << "\n";
        return result_json;
    }

    return "";
}


