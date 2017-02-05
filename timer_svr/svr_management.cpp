#include "svr_management.h"

#include <algorithm>
#include <iostream>

worker_svr_management * worker_svr_management::instance = nullptr;

worker_svr_management::worker_svr_management()
    : svr_bev_list()
{

}

worker_svr_management *worker_svr_management::getInstance()
{
    if(instance == nullptr) {
        instance = new worker_svr_management();
    }

    return instance;
}

void worker_svr_management::add_worker_svr(bufferevent *bev)
{
    if(std::find(svr_bev_list.begin(), svr_bev_list.end(), bev) == svr_bev_list.end())
        this->svr_bev_list.emplace_back(bev);
    else
        ;

    return ;
}

void worker_svr_management::del_worker_svr(bufferevent *bev)
{
    if(std::find(svr_bev_list.begin(), svr_bev_list.end(), bev) != svr_bev_list.end())
        this->svr_bev_list.remove(bev);
}

int worker_svr_management::senddata_to(bufferevent *bev, std::string msg)
{
    if(std::find(svr_bev_list.begin(), svr_bev_list.end(), bev) == svr_bev_list.end()) {
        std::cout << "[worker_svr_management.cpp:" << __LINE__ << "]: bev is not find.\n";
        return -1;
    }

    struct evbuffer /**input,*/ *output;

    //input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    msg.append("\n");
    evbuffer_add(output, msg.c_str(), msg.length());

    return 0;
}

/****
 *
 *
 */

static struct bufferevent *g_gateway_bev = nullptr;

void set_gateway_bev(struct bufferevent *bev)
{
    if(bev == nullptr) {
        std::cout << "[svr_management.cpp:" << __LINE__ << "]: bev is null.\n";
    }

    g_gateway_bev = bev;
}

void write_data_to_gateway(std::string &&msg)
{
    struct evbuffer /**input,*/ *output;

    if(g_gateway_bev == nullptr) {
        std::cout << "[svr_management.cpp:" << __LINE__ << "]: g_gateway_bev is null.\n";
        return ;
    }

    //input = bufferevent_get_input(bev);
    output = bufferevent_get_output(g_gateway_bev);

    msg.append("\n");
    evbuffer_add(output, msg.c_str(), msg.length());
}
