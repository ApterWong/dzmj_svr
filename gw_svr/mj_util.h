#ifndef MJ_UTIL_H
#define MJ_UTIL_H

#include "stdafx.h"

namespace mj_util {

std::string mj_itoa(uint64_t num);

bool mj_atoi(const std::string &s_num, uint64_t &num);

}
#endif // MJ_UTIL_H
