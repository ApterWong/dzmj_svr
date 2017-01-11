#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H

#include <string>
#include <json11.hpp>
using namespace std;
using namespace json11;

class abstract_request
{
public:
    abstract_request();

    virtual std::string handler() = 0;

private:

};

#endif // ABSTRACT_REQUEST_H
