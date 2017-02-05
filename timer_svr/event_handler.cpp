#include "event_handler.h"
#include "svr_management.h"
#include "mj_util.h"

#include <cstring>
#include <string>
#include <iostream>

#include "json11.hpp"
using namespace json11;
using namespace std;

/***
 *  @json: worker_svr发来的json数据
 *  @arg: event_base
 */
static string do_worker(Json &json, void *arg);

void do_accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int socklen, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    struct bufferevent *bev;

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(!bev) {
        perror("bufferevent_socket_new");
        return ;
    }

    bufferevent_setcb(bev, do_connect_read, do_connect_write, do_connect_error,
                      NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void do_signal(evutil_socket_t fd, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;

    cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "signal event..." << endl;

    timeval tm{2,0};
    event_base_loopexit(base, &tm);
}

void do_connect_read(struct bufferevent *bev, void *arg)
{
    struct evbuffer *input, *output;
    char *buf;
    size_t  rdbuflen = 0;
    string json_err;

    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while(1)
    {
        buf = evbuffer_readln(input, &rdbuflen, EVBUFFER_EOL_ANY);
        if(NULL == buf) {
            break;
        }

        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << bufferevent_getfd(bev) << " " << "recv " << rdbuflen << " :"
             << buf << endl;

        Json json = Json::parse(buf, json_err);
        if(json == nullptr) {
            free(buf);
            continue;
        }

        if(json["server"].string_value() == "gateway") {
            set_gateway_bev(bev);
        }
        else if(json["server"].string_value() == "worker") {
            //添加bev到worker_svr_management
            worker_svr_management *instance = worker_svr_management::getInstance();
            instance->add_worker_svr(bev);
        }
        else {
            /*
            string bev_string = mj_util::mj_itoa((uint64_t)bev);
            json = Json::object({
                                    {"data", json},
                                    {"bev", bev_string}
                                });*/
            do_worker(json, arg);
        }


        free(buf);
    }
}

void do_connect_write(struct bufferevent *bev, void *arg)
{
    (void)bev;
    (void)arg;
}

void do_connect_error(struct bufferevent *bev, short event, void *)
{
    if(event & BEV_EVENT_EOF){
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << bufferevent_getfd(bev) << " is closed." << endl;
    }
    else if(event & BEV_EVENT_ERROR) {
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << bufferevent_getfd(bev) << " has a error." << endl;
        perror("do_connect_error");
    }

    bufferevent_free(bev);
}

string do_worker(Json &json, void *arg)
{
    if(json == nullptr)
        return "";

    {
        struct timeval tm;

        //取出超时时间(单位ms)
        int timeout = json["timeout"].int_value();
        // 服务器不允许的超时时间
        if(timeout < 5000 || timeout > 15000)
            return "";

        tm.tv_usec = timeout * 1000;

        Json *data = new Json(json);
        struct event *tmev = event_new((struct event_base *)(arg), -1, EV_TIMEOUT, on_timer_hander, (void *)(data));
        event_add(tmev, &tm);
    }

    return "";
}


void on_timer_hander(int, short, void *arg)
{
    Json *json = reinterpret_cast<Json*>(arg);
    if(json == nullptr || *json == nullptr) {
        cout << "[event_handler.cpp:" << __LINE__ << "] arg err: arg=" << arg << "\n";
        return ;
    }

    //构造的超时请求
    int type = (*json)["type"].int_value();
    string roomid = (*json)["roomid"].string_value();
    int count = (*json)["count"].int_value();

    Json result;

    if(type == 1) {
        result = Json::object({
                                  {"action", 3},
                                  {"cmd", "timeout"},
                                  {"timout", "chupai"},
                                  {"roomid", roomid},
                                  {"tmout_id", count}
                              });

        write_data_to_gateway(result.dump());
    }
    else if(type == 2) {
        result = Json::object({
                                  {"action", 3},
                                  {"cmd", "timeout"},
                                  {"timout", "hgpc"},
                                  {"roomid", roomid},
                                  {"tmout_id", count}
                              });

        write_data_to_gateway(result.dump());
    }
    else {
        cout << "[event_handler.cpp:" << __LINE__ << "]: unknow the timeout type.\n";
    }

    //delete
    delete json;
}
