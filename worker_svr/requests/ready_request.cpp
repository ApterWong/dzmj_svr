#include "ready_request.h"
#include "redis_cli/redis_support.h"
#include "gamestart_request.h"

ready_request::ready_request(Json &json)
{
    user_id = json["user_id"].string_value();
    ready = json["ready"].bool_value();
}

string ready_request::handler()
{
    CRedisClient *rds = redis_instance::getInstance();

    string key = "readylist";
    string result;
    int waitlist_count = 0;
    try{
        if(ready == true)
            rds->sadd(key, user_id);
        else
            rds->srem(key, user_id);
        waitlist_count = rds->scard(key);
    }
    catch(CRedisException &e) {
        cout << "[ready_request.cpp:" << __LINE__ << "] " << "redis err:" << e.what() << "\n";
        return "";
    }

    // 返回结果
    if(ready) {
        /*{"cli_data":{"type":"game", "cmd":"_cmd_", "_cmd-response_":"", "status":"ok", "msg":"_msg_", "what":"???"
             }, "user_id":"_uid_"}*/
        Json json = Json::object({{"type", "game"}, {"cmd", "ready"}, {"status", "ok"},
                                 {"ready", true}});
        json = Json::object({{"cli_data", json}, {"user_id", user_id}});
        result = json.dump() + "\n";
    }
    else
    {
        Json json = Json::object({{"type", "game"}, {"cmd", "ready"}, {"status", "ok"},
                                 {"ready", false}});
        json = Json::object({{"cli_data", json}, {"user_id", user_id}});
        result = json.dump() + "\n";
    }

    if(waitlist_count >= 4) {
        vector<string> users;
        string values;

        for(int i=0; i<4; i++) {
            rds->spop(key, &values);
            users.push_back(values);
        }

        gamestart_request start_handler(users);
        result += start_handler.handler();
    }

    return result;
}
