#ifndef WORKER_SVR_MANAGEMENT_H
#define WORKER_SVR_MANAGEMENT_H

#include <list>
#include <string>

#include "stdafx.h"

class worker_svr_management
{
    worker_svr_management();
public:
    static worker_svr_management *getInstance();

    void add_worker_svr(struct bufferevent* bev);
    void del_worker_svr(struct bufferevent* bev);

    int senddata_to(struct bufferevent* bev, std::string msg);

private:
    std::list<struct bufferevent*> svr_bev_list;

    static worker_svr_management *instance;
};

void set_gateway_bev(struct bufferevent* bev);

void write_data_to_gateway(std::__cxx11::string &&msg);

#endif // WORKER_SVR_MANAGEMENT_H
