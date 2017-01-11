#include "dispatcher.h"
#include "stdafx.h"
#include "mj_util.h"
#include "login_svr_handler.h"
#include "worker_svr_handler.h"

#include "json11.hpp"
using namespace json11;

void dispatch_command(const char *data, void *bev_address)
{
    cout << "[" << "dispatcher.cpp" << ":" << __LINE__ << "] " << data << "\t" << bev_address << endl;

    int action_type = 0;
    string json_err;
    Json json = Json::parse(data, json_err);

    if(json == nullptr)
    {
        cout << "[" << "dispatcher.cpp" << ":" << __LINE__ << "] " << "dispatch_command err:" << json_err << "\n";
        return ;
    }

    if(json["action"].type() != Json::NUMBER)
    {
        cout << "[" << "dispatcher.cpp" << ":" << __LINE__ << "] " << "dispatch_command err: action err.\n";
        return ;
    }

    action_type = json["action"].int_value();

    switch(action_type)
    {
    case action_login:
    {
        string bev_string = mj_util::mj_itoa((uint64_t)bev_address);
        string uni_key = mj_util::create_uuid();

        uint64_t xxx;
        if( mj_util::mj_atoi(bev_string, xxx) == false) {
            cout << "[dispatcher.cpp:" << __LINE__ << "] bev_string to l_key error:" << bev_string << "\n";
            break;
        }

        L_KEY key = (L_KEY)xxx;
        // 记录好unikey, login返回数据时验证, 若不对可能是cli发送完登录请求就关闭了链接
        map_bev2unikey[key] = uni_key;

        json = Json({{"cli_data", json}, {"bev", bev_string}, {"uni_key", uni_key}});
        write_data_to_login_svr(json.dump().c_str());

        break;
    }
    case action_logout:
        break;
    case action_cmd:
    {
        string user_id = json["user_id"].string_value();

        // 验证是否登录
        if(user_id.empty() || map_userid2bev.find(user_id) == map_userid2bev.end())
            break;

        json = Json::object({{"cli_data", json}, {"user_id", user_id}});
        write_data_to_worker_svr(json.dump().c_str());

        break;
    }
    default:
        cout << "[dispatcher.cpp:" << __LINE__ << "] " << "unknow cmd.\n";
        break;
    }

    cout << "[" << "dispatcher.cpp" << ":" << __LINE__ << "] " << json.dump() << endl;
}
