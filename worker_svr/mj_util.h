#ifndef MJ_UTIL_H
#define MJ_UTIL_H

#include "stdafx.h"

namespace mj_util {
    static const char cardSet[] = {
        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',//万
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',//条
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',//筒
        'A', 'B', 'C', 'D', 'E', 'F', 'G',          //风

        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G',

        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G',

        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G'
    };

    enum MJ_CARDS{
        MJ_noCard = 0,
        MJ_JIUWAN = 'r', MJ_BAWAN, MJ_QIWAN, MJ_LIUWAN, MJ_WUWAN, MJ_SIWAN, MJ_SANWAN, MJ_ERWAN, MJ_YIWAN,
        MJ_JIUTIAO = 'a', MJ_BATIAO, MJ_QITIAO, MJ_LIUTIAO, MJ_WUTIAO, MJ_SITIAO, MJ_SANTIAO, MJ_ERTIAO, MJ_YITIAO,
        MJ_JIUTONG = 'R', MJ_BATONG, MJ_QITONG, MJ_LIUTONG, MJ_WUTONG, MJ_SITONG, MJ_SANTONG, MJ_ERTONG, MJ_YITONG,
        MJ_BAN = 'A', MJ_FA, MJ_ZHONG, MJ_BEI, MJ_XI, MJ_NAN, MJ_DONG,
        MJ_WANG = '0', MJ_ANGNG='*', MJ_OTHERNEWCARD='#'
    };

    std::string mj_itoa(uint64_t num);

    std::string create_uuid();

    bool mj_atoi(const std::string &s_num, uint64_t &num);

    std::string create_roomname();

    int create_saizi_number();

}
#endif // MJ_UTIL_H
