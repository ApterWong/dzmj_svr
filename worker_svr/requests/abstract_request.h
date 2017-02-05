#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H

#include <string>
#include <json11.hpp>
using namespace std;
using namespace json11;

#include "data_model/mj_roomprocess.h"

/* *  return data format
 * {"cli_data":{"type":"game", "cmd":"_cmd_", "_cmd-response_":"", "status":"ok", "msg":"_msg_", "what":"???"
     }, "user_id":["_uid_",...]}
 */
class abstract_request
{
public:
    abstract_request();

    virtual std::string handler() = 0;

private:

};

#endif // ABSTRACT_REQUEST_H
