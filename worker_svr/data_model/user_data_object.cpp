#include "user_data_object.h"
#include "data_convert.h"

#include <cstring>
#include <QString>

#include <iostream>

user_data_object_t::user_data_object_t()
{
    memset(this, 0, sizeof(user_data_object_t));
}

/***
 *
*/
user_data_object user_data_object_new()
{
    return shared_ptr<user_data_object_t>(new user_data_object_t());
}

std::string user_data_to_hex(user_data_object &obj)
{
    std::string data;

    char buf[1024] = {0};
    ObjToHex(buf, obj.get(), sizeof(user_data_object::element_type));

    data.append(buf);

    std::cout << "构造了一个user hex string:" << buf << std::endl;
    return std::move(data);
}

string other_user_data_to_hex(user_data_object &obj)
{
    struct other_user_data_object_t other;

    memcpy(other.chi, obj->chi, 16);
    memcpy(other.gang, obj->gang, 8);
    memcpy(other.peng, obj->peng, 8);
    memcpy(other.gpc_seq, obj->gpc_seq, 8*sizeof(int));
    other.gpc_seq_count = obj->gpc_seq_count;
    other.id = obj->self_id;
    other.NewCard = obj->NewCard;
    other.paiCount = obj->paiCount;
    other.paiRecCount = obj->paiRecCount;
    other._c = obj->_c;
    other._g = obj->_g;
    other._p = obj->_p;

    char *data = new char[sizeof(other)*2 + 1];
    ObjToHex(data, &other, sizeof(other));

    std::cout << "构造了一个other_user hex string:" << data << std::endl;
    string ret(data);
    delete[] data;

    return ret;
}
