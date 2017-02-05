#include "bev_manager.h"
#include "stdafx.h"

#include <iostream>

static struct bufferevent *gateway_bev;
static struct bufferevent *worker_bev;
static struct bufferevent *login_bev;

void set_gateway_bev(struct bufferevent *bev)
{
    gateway_bev = bev;
}

void set_login_bev(struct bufferevent *bev)
{
    login_bev = bev;
}

void set_worker_bev(struct bufferevent *bev)
{
    worker_bev = bev;
}


void write_data_to_login(string &msg)
{
    if(login_bev == NULL) {
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "write_data_to_login err: login_bev is null point\n";
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "msg:" << msg << "\n";
        return ;
    }

    struct evbuffer *out;

    out = bufferevent_get_output(login_bev);

    msg.append("\n");
    evbuffer_add(out, msg.c_str(), msg.length());
}

void write_data_to_worker(string &msg)
{
    if(worker_bev == NULL) {
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "write_data_to_worker err: worker_bev is null point\n";
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "msg:" << msg << "\n";
        return ;
    }

    struct evbuffer *out;

    out = bufferevent_get_output(worker_bev);

    msg.append("\n");
    evbuffer_add(out, msg.c_str(), msg.length());
}

void write_data_to_gateway(string &msg)
{
    if(gateway_bev == NULL) {
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "write_data_to_gateway err: gateway_bev is null point\n";
        cout << "[" << "bev_manager.cpp" << ":" << __LINE__ << "] " << "msg:" << msg << "\n";
        return ;
    }

    struct evbuffer *out;

    out = bufferevent_get_output(gateway_bev);

    msg.append("\n");
    evbuffer_add(out, msg.c_str(), msg.length());
}
