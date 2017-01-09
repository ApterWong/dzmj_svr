#include "dispatcher.h"
#include "stdafx.h"
#include "mj_util.h"

#include "json11.hpp"
using namespace json11;

void dispatch_command(const char *data, void *bev_address)
{
    cout << data << "\t" << bev_address << endl;

    int action_type = 0;
    string json_err;
    Json json = Json::parse(data, json_err);

    if(json == nullptr)
    {
        cout << "dispatch_command err:" << json_err << "\n";
        return ;
    }

    if(json["action"].type() != Json::NUMBER)
    {
        cout << "dispatch_command err: action err.\n";
        return ;
    }

    action_type = json["action"].int_value();

    string bev_string = mj_util::mj_itoa((uint64_t)bev_address);
    json = Json({{"cli_data", json}, {"bev", bev_string}});

    switch(action_type)
    {
    case action_login:
        break;
    case action_logout:
        break;
    case action_cmd:
        break;
    default:
        break;
    }

    cout << json.dump() << endl;
}
