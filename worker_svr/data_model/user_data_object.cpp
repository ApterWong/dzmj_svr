#include "user_data_object.h"
#include "util/data_convert.h"

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


user_data_process::user_data_process()
{

}

user_data_process::~user_data_process()
{

}

void user_data_process::set_user_data_object(user_data_object &o)
{
    this->obj = o;
}

user_data_object user_data_process::get_user_data_object() const
{
    return this->obj;
}

int user_data_process::chupai(const char card)
{
    if(card != obj->NewCard)
    {
        int i=0;
        for(; i<obj->paiCount; i++)
        {
            if(obj->paiList[i] == card)
            {
                for(int j=i; j<obj->paiCount; j++)
                    obj->paiList[j] = obj->paiList[j+1];
                obj->paiList[obj->paiCount-1] = obj->NewCard;
            }
        }

        if(i == obj->paiCount)
            return -1;

        return 0;
    }

    // 添加到已出牌
    obj->paiRecList[obj->paiRecCount++] = card;

    return 0;
}

int user_data_process::test_chi(const char card)
{
    bool flag = false;

    // err
    if(obj->cChiCount <= 0 || obj->cChiCount >=16)
        return flag;

    for_each(obj->cChiList, obj->cChiList+obj->cChiCount-1, [&](const char c){
        if(card == c)
            flag = true;
    });

    return flag;
}

int user_data_process::test_peng(const char card)
{
    bool flag = false;

    // err
    if(obj->cPengCount <= 0 || obj->cPengCount >=16)
        return flag;

    for_each(obj->cPengList, obj->cPengList+obj->cPengCount-1, [&](const char c){
        if(card == c)
            flag = true;
    });

    return flag;
}

int user_data_process::test_gang(const char card)
{
    bool flag = false;

    // err
    if(obj->cGangCount <= 0 || obj->cGangCount >=16)
        return flag;

    for_each(obj->cGangList, obj->cGangList+obj->cGangCount-1, [&](const char c){
        if(card == c)
            flag = true;
    });

    return flag;
}

int user_data_process::test_hu(const char card)
{
    bool flag = false;

    // err
    if(obj->cHuCount <= 0 || obj->cHuCount >=16)
        return flag;

    for_each(obj->cHuList, obj->cHuList+obj->cHuCount-1, [&](const char c){
        if(card == c)
            flag = true;
    });

    return flag;
}

void user_data_process::setHu_list(const char *hu, int hc)
{
    memcpy(obj->cHuList, hu, hc);
    obj->cHuCount = hc;
}

void user_data_process::setGang_list(const char *gang, int hc)
{
    memcpy(obj->cGangList, gang, hc);
    obj->cGangCount = hc;
}

void user_data_process::setPeng_list(const char *peng, int hc)
{
    memcpy(obj->cPengList, peng, hc);
    obj->cPengCount = hc;
}

void user_data_process::setChi_list(const char *chi, int hc)
{
    memcpy(obj->cChiList, chi, hc);
    obj->cChiCount = hc;
}
