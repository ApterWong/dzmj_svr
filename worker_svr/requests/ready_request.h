#ifndef READY_REQUEST_H
#define READY_REQUEST_H

#include "abstract_request.h"

class ready_request : public abstract_request
{
public:
    ready_request(Json &json);
    string handler();
private:
    string user_id;
    bool ready;
};

#endif // READY_REQUEST_H
