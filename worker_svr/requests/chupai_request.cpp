#include "chupai_request.h"

chupai_request::chupai_request(Json &json)
{
    roomid = json["roomid"].string_value();
    user_id = json["user_id"].string_value();
    card = (char)json["chupai"].int_value();
}

string chupai_request::handler()
{
    try{

    }
    catch(...){

    }
}
