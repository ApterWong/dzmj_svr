#include "ready_request.h"
#include "redis_cli/redis_support.h"

ready_request::ready_request(Json &json)
{
    user_id = json["user_id"].string_value();
    ready = json["ready"].bool_value();
}

string ready_request::handler()
{
    CRedisClient *rds = redis_instance::getInstance();

    string key = "readylist";
    int waitlist_count = 0;
    try{
        rds->sadd(key, user_id);
        waitlist_count = rds->scard(key);
    }
    catch(CRedisException &e) {
        cout << "[ready_request.cpp:" << __LINE__ << "] " << "redis err:" << e.what() << "\n";

    }

    if(waitlist_count >= 4) {




    }
}
