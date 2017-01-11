#include "event_handler.h"
#include "cache_svr_handler.h" // use  write_data_to_cache_svr()

#include <cstring>
#include <string>
#include <iostream>

#include "json11.hpp"
using namespace json11;

using namespace std;

static string do_worker(const char *buf);
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

        if(buf == NULL || strlen(buf) == 0)
        {
            free(buf);
            continue;
        }

        string res = do_worker(buf);

        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "do worker's result size:" << res.length() <<  " data: " << res << endl;

        if(res.empty())
        {
           free(buf);
           continue;
        }

        res.append("\n");
        evbuffer_add(output, res.c_str(), res.length());

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
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << bufferevent_getfd(bev) << " is closed." << endl;
    }
    else if(event & BEV_EVENT_ERROR) {
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << bufferevent_getfd(bev) << " has a error." << endl;
        perror("do_connect_error");
    }

    bufferevent_free(bev);
}

string do_worker(const char *buf)
{
    string json_err;
    Json json = Json::parse(buf, json_err);
    if(json == nullptr) {
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " <<
                "do_worker():" << json_err << "\n";
        return "";
    }

    string user_id = json["user_id"].string_value();
    json = json["cli_data"];



}
