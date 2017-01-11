#include "mj_util.h"

#include "data_convert.h"

#include <algorithm>
#include <uuid/uuid.h>

std::string mj_util::mj_itoa(uint64_t num)
{
    int i=0;
    char buf[64] = {0};

    if(num == 0)
        return std::string("0");

    while(num)
    {
        buf[i++] = num % 10 + '0';
        num /= 10;
    }

    std::string str(buf);
    std::reverse(str.begin(), str.end());

    return str;
}


bool mj_util::mj_atoi(const std::string &s_num, uint64_t &res)
{
    if(!std::all_of(s_num.begin(), s_num.end(), [](char c){ return c >= '0' && c <= '9';}))
        return false;

    int len = s_num.size();
    uint64_t num = 0;

    for(int i=0; i<len; i++)
    {
        num *= 10;
        num += s_num[i] - '0';
    }

    res = num;
    return true;
}

string mj_util::create_uuid()
{
    uuid_t uuid;
    uuid_generate(uuid);

    char ss_buf[64] = {0};
    int ret = ObjToHex(ss_buf, uuid, sizeof(uuid));
    if(ret != 0) {
        return "";
    }

    return string(ss_buf);
}
