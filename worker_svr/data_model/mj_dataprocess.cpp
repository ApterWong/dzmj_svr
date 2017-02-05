#include "mj_dataprocess.h"

#include <cstring>
#include <algorithm>


mj_dataprocess::mj_dataprocess()
{

}

mj_dataprocess::~mj_dataprocess()
{

}

void mj_dataprocess::set_user_data_object(user_data_object &o)
{
    this->obj = o;
}

user_data_object mj_dataprocess::get_user_data_object() const
{
    return this->obj;
}

int mj_dataprocess::chupai(const char card)
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

int mj_dataprocess::test_chi(const char card)
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

int mj_dataprocess::test_peng(const char card)
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

int mj_dataprocess::test_gang(const char card)
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

int mj_dataprocess::test_hu(const char card)
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

void mj_dataprocess::setHu_list(const char *hu, int hc)
{
    memcpy(obj->cHuList, hu, hc);
    obj->cHuCount = hc;
}

void mj_dataprocess::setGang_list(const char *gang, int hc)
{
    memcpy(obj->cGangList, gang, hc);
    obj->cGangCount = hc;
}

void mj_dataprocess::setPeng_list(const char *peng, int hc)
{
    memcpy(obj->cPengList, peng, hc);
    obj->cPengCount = hc;
}

void mj_dataprocess::setChi_list(const char *chi, int hc)
{
    memcpy(obj->cChiList, chi, hc);
    obj->cChiCount = hc;
}
