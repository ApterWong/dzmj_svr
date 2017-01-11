#include "redis_support.h"

CRedisClient *redis_instance::rediscli = nullptr;

redis_instance::redis_instance()
{

}

CRedisClient *redis_instance::getInstance()
{
    if(rediscli == nullptr)
    {
        rediscli = new CRedisClient("127.0.0.1:6379");
    }

    return rediscli;
}
