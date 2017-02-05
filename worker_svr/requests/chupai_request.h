#ifndef CHUPAI_REQUEST_H
#define CHUPAI_REQUEST_H

#include "abstract_request.h"

class chupai_request : public abstract_request
{
public:
    chupai_request(Json &json);

    string handler();

private:
    string roomid;
    string user_id;
    char card;
};

#endif // CHUPAI_REQUEST_H
