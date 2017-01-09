#ifndef REDIS_INSTANCE_H
#define REDIS_INSTANCE_H

#include "r3c/r3c.h"
using namespace r3c;

class redis_instance
{
    redis_instance();
public:
    static CRedisClient *getInstance();
private:
    static CRedisClient *rediscli;// = CRedisClient("127.0.0.1:6379");
};

#endif // REDIS_INSTANCE_H
