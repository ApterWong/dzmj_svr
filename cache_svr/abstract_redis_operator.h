#ifndef ABSTRACT_REDIS_OPERATOR_H
#define ABSTRACT_REDIS_OPERATOR_H
#include "json11.hpp"
using namespace json11;

#include <string>
using namespace std;

class abstract_redis_operator
{
public:
    abstract_redis_operator();

    virtual string handler() = 0;
};

#endif // ABSTRACT_REDIS_OPERATOR_H
