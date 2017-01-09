#ifndef LOGOUT_OPERATOR_H
#define LOGOUT_OPERATOR_H
#include "abstract_redis_operator.h"

class logout_operator : public abstract_redis_operator
{
public:
    logout_operator(string &uid, string &ss, string bev);

    string handler();

private:
    string user_id, session, bev_string;
};

#endif // LOGOUT_OPERATOR_H
