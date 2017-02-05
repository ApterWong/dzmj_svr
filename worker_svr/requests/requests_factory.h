#ifndef REQUESTS_FACTORY_H
#define REQUESTS_FACTORY_H

#include "agang_request.h"
#include "chi_request.h"
#include "chupai_request.h"
#include "gang_request.h"
#include "hu_request.h"
#include "peng_request.h"
#include "ready_request.h"
#include "tuoguan_request.h"
#include "zgang_request.h"

#include "json11.hpp"
using namespace json11;

class requests_factory
{
public:
    requests_factory();

    static abstract_request *create_request(Json &json);

private:

};

#endif // REQUESTS_FACTORY_H
