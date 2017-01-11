#ifndef REDIS_SUPPORT_H
#define REDIS_SUPPORT_H

#include <r3c/r3c.h>
using namespace r3c;

class redis_instance
{
    redis_instance();
public:
    static CRedisClient *getInstance();
private:
    static CRedisClient *rediscli;// = CRedisClient("127.0.0.1:6379");
};

#endif // REDIS_SUPPORT_H
