#include "mj_util.h"

#include "data_convert.h"

#include <algorithm>
#include <uuid/uuid.h>
#include <atomic>
#include <time.h>
#include <stdlib.h>

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

std::string mj_util::create_uuid()
{
    uuid_t uuid;
    uuid_generate(uuid);

    char ss_buf[64] = {0};
    int ret = ObjToHex(ss_buf, uuid, sizeof(uuid));
    if(ret != 0) {
        return "";
    }

    return std::string(ss_buf);
}

std::string mj_util::create_roomname()
{
    static std::atomic_ushort range = ATOMIC_FLAG_INIT;

    struct timeval tm;
    gettimeofday(&tm, NULL);

    uint64_t name = tm.tv_sec *100000 + range.load();

    range.fetch_add(1);

    return mj_itoa(name);
}

int mj_util::create_saizi_number()
{
    srand(time(NULL));
    return rand()%6+1;
}
