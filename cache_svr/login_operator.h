#ifndef LOGIN_REDIS_OPERATOR_H
#define LOGIN_REDIS_OPERATOR_H

#include "abstract_redis_operator.h"

/****
 *      -hash key-
 *  user_id: uid
 *  session: session
 *  status:  online | offline | gaming | leave
 */
class login_operator : public abstract_redis_operator
{
public:
    login_operator(string &uid, string &ss, string &bev);

    string handler();

private:
    string user_id, session, bevstring;
};

#endif // LOGIN_REDIS_OPERATOR_H
