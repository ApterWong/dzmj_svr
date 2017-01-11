#include "user_data_object.h"
#include <cstring>

user_data_object_t::user_data_object_t()
{
    memset(this, 0, sizeof(user_data_object_t));
}

user_data_object user_data_object_new()
{
    return user_data_object(new user_data_object_t());
}
