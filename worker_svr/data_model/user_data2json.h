#ifndef USER_DATA2JSON_H
#define USER_DATA2JSON_H

#include "user_data_object.h"
#include "json11.hpp"
using namespace json11;

class user_data2json
{
public:
    user_data2json();

    void setObject(user_data_object &obj);

    Json getUserJsonData();
    Json getOtherUserJsonData();

private:
    user_data_object data;
    bool valid;
};

#endif // USER_DATA2JSON_H
