#include "event_handle.h"
#include "dispatcher.h"

#include "mj_util.h"
#include "json11.hpp"
using namespace json11;

void do_accept(struct evconnlistener *, evutil_socket_t fd, struct sockaddr *, int , void *arg)
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
    bufferevent_enable(bev, EV_READ/* | EV_WRITE*/);
}

void do_signal(int, short, void *arg)
{
    struct event_base *base = (struct event_base *)arg;

    cout << "signal event..." << endl;

    timeval tm{2,0};
    event_base_loopexit(base, &tm);
}

void do_connect_read(bufferevent *bev, void *)
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

        dispatch_command(buf, (void*)bev);

        free(buf);
    }
}

void do_connect_write(bufferevent *bev, void *arg)
{
    (void)bev;
    (void)arg;
}

void do_connect_error(bufferevent *bev, short event, void *)
{
    if(event & BEV_EVENT_EOF){
        cout << "client " << bufferevent_getfd(bev) << " is closed." << endl;
    }
    else if(event & BEV_EVENT_ERROR) {
        cout << bufferevent_getfd(bev) << " has a error." << endl;
        perror("do_connect_error");
    }

    //erase map
    if(map_bev2userid.find(bev) != map_bev2userid.end())
        map_bev2userid.erase(bev);

    bufferevent_free(bev);
}


void do_login_recv(const char *buf)
{
    string err_string;

    Json json = Json::parse(buf, err_string);
    if(json == nullptr)
    {
        cout << "handler_for_login_recv:" << err_string << "\n";
        return;
    }

    if(json["cli_data"].type() != Json::OBJECT || json["bev"].type() != Json::STRING)
    {
        cout << "handler_for_login_recv: (json object err.)\n";
        return ;
    }

    string bev_string = json["bev"].string_value();
    struct bufferevent *bev = nullptr;
    uint64_t ptr;

    if(!mj_util::mj_atoi(bev_string, ptr))
    {
        cout << "handler_for_login_recv: (bev_string error.)\n";
        return;
    }

    bev = (struct bufferevent *)ptr;
    json = json["cli_data"];

    string user_id;
    int action;

    user_id = json["user_id"].string_value();
    action = json["action"].int_value();
    if(action == action_login)
    {
        if(json["status"].type() == Json::STRING &&
                json["status"].string_value() == string("ok"))
            map_bev2userid[bev] = user_id;
    }
    else if(action == action_logout)
    {

    }


    /***  send data */
    string msg = json.dump();
    msg.append("\n");
    evbuffer *out = bufferevent_get_output(bev);
    evbuffer_add(out, msg.c_str(), msg.length());
}

void do_worker_recv(const char *buf)
{
    string err_string;
    Json json = Json::parse(buf, err_string);
    if(json == nullptr)
    {
        cout << "handler_for_worker_recv:" << err_string << "\n";
        return;
    }

    if(json["cli_data"].type() != Json::OBJECT || json["bev"].type() != Json::STRING)
    {
        cout << "handler_for_worker_recv: (json object err.)\n";
        return ;
    }

    string bev_string = json["bev"].string_value();
    struct bufferevent *bev = nullptr;
    uint64_t ptr;

    if(!mj_util::mj_atoi(bev_string, ptr))
    {
        cout << "handler_for_worker_recv: (bev_string error.)\n";
        return;
    }

    bev = (struct bufferevent *)ptr;
    json = json["cli_data"];

    /***  send data */
    string msg = json.dump();
    msg.append("\n");
    evbuffer *out = bufferevent_get_output(bev);
    evbuffer_add(out, msg.c_str(), msg.length());
}


void do_cache_recv(const char *buf)
{
    string err_string;
    Json json = Json::parse(buf, err_string);
    if(json == nullptr)
    {
        cout << "handler_for_cache_recv:" << err_string << "\n";
        return;
    }

    if(json["cli_data"].type() != Json::OBJECT || json["bev"].type() != Json::STRING)
    {
        cout << "handler_for_cache_recv: (json object err.)\n";
        return ;
    }

    string bev_string = json["bev"].string_value();
    struct bufferevent *bev = nullptr;
    uint64_t ptr;

    if(!mj_util::mj_atoi(bev_string, ptr))
    {
        cout << "handler_for_worker_recv: (bev_string error.)\n";
        return;
    }

    bev = (struct bufferevent *)ptr;
    json = json["cli_data"];

    /***  send data */
    string msg = json.dump();
    msg.append("\n");
    evbuffer *out = bufferevent_get_output(bev);
    evbuffer_add(out, msg.c_str(), msg.length());
}
