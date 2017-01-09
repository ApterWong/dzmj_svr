#include "event_handler.h"
#include "bev_manager.h"

#include "login_operator.h"
#include "logout_operator.h"

#include <cstring>
#include <string>
#include <iostream>

#include "json11.hpp"
using namespace json11;
using namespace std;

static string do_worker(Json &json);
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

    cout << "signal event..." << endl;

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

        cout << bufferevent_getfd(bev) << " " << "recv " << rdbuflen << " :"
             << buf << endl;

        Json json = Json::parse(buf, json_err);
        if(json == nullptr) {
            free(buf);
            continue;
        }
        if(json["server"].string_value() == "login") {
            set_login_bev(bev);
        }
        else if(json["server"].string_value() == "gateway") {
            set_gateway_bev(bev);
        }
        else if(json["server"].string_value() == "worker") {
            set_worker_bev(bev);
        }
        else {
            string res = do_worker(json);

            cout << "do worker's result size:" << res.length() <<  " data: " << res << endl;

            //正常执行, 没有特别情况需要反馈
            if(res.empty())
            {
                free(buf);
                continue;
            }

            res.append("\n");
            evbuffer_add(output, res.c_str(), res.length());
        }

        free(buf);
    }
}

void do_connect_write(struct bufferevent *bev, void *arg)
{
    (void)bev;
    (void)arg;
}

void do_connect_error(struct bufferevent *bev, short event, void *arg)
{
    if(event & BEV_EVENT_EOF){
        cout << bufferevent_getfd(bev) << " is closed." << endl;
    }
    else if(event & BEV_EVENT_ERROR) {
        cout << bufferevent_getfd(bev) << " has a error." << endl;
        perror("do_connect_error");
    }

    bufferevent_free(bev);
}

string do_worker(Json &json)
{
    if(json == nullptr)
        return "";

    abstract_redis_operator *hand = nullptr;
    string action = json["action"].string_value();
    string bev    = json["bev"].string_value();

    if(action == "login") {
        string user_id = json["user_id"].string_value();
        string session = json["session"].string_value();

        hand = new login_operator(user_id, session, bev);
        string result = hand->handler();

        // send data to gw
        if(!result.empty())
            write_data_to_gateway(result);
    }
    else if(action == "logout") {
        string user_id = json["user_id"].string_value();
        string session = json["session"].string_value();

        hand = new logout_operator(user_id, session, bev);
        string result = hand->handler();

        if(!result.empty())
            write_data_to_gateway(result);
    }
    else if(action == "modify") {
        string user_id = json["user_id"].string_value();
        string session = json["session"].string_value();

        hand = 0;
        string result = hand->handler();

        if(!result.empty())
            write_data_to_gateway(result);
    }

    return "";
}
