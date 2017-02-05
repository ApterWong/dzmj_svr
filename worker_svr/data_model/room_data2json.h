#ifndef ROOM_DATA2JOSN_H
#define ROOM_DATA2JOSN_H

#include "room_data_object.h"
#include "json11.hpp"
using namespace json11;

class room_data2Json
{
public:
    room_data2Json();

    void setObject(room_data_object &obj);
    Json getRoomJsonData();

private:
    room_data_object data;
    bool valid;
};

#endif // ROOM_DATA2JOSN_H
