#include "requests_factory.h"

requests_factory::requests_factory()
{

}

abstract_request *requests_factory::create_request(Json &json)
{
    string type = json["cmd"].string_value();
    abstract_request *request = nullptr;

    if(type == "ready") {
        request = new ready_request(json);
    }
    else if(type == "tuoguan") {

    }
    else if(type == "chupai") {

    }
    else if(type == "hu") {

    }
    else if(type == "gang") {

    }
    else if(type == "zgang") {

    }
    else if(type == "agang") {

    }
    else if(type == "peng") {

    }
    else if(type == "chi") {

    }
    else if(type == "cancel") {

    }
    else {
        //...
    }

    return request;
}
