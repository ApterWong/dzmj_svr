#include "room_data_object.h"

#include <cstring>

room_data_object_t::room_data_object_t()
{
    memset(this, 0, sizeof(room_data_object_t));
}

room_data_object room_data_object_new()
{
    return room_data_object(new room_data_object_t());
}
