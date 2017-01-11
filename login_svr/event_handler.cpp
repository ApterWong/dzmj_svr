#include "event_handler.h"
#include "cache_svr_handler.h" // use  write_data_to_cache_svr()

#include <cstring>
#include <string>
#include <iostream>

#include "json11.hpp"
using namespace json11;

#include "data_convert.h"

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
    string user_name, user_pwd, err_string, bev_string, unikey;
    string user_id, session;
    int type;

    Json json = Json::parse(buf, err_string);
    if(json == nullptr)
    {
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "do_worker err:" << err_string << "\n";
        string err = R"({"action":"login", "status":"error", "what":"server error."})";
        string e;
        Json err_json = Json::parse(err, e);

        err_json = Json::object({{"cli_data", err_json}, {"bev", bev_string}});
        return err_json.dump();
    }

    bev_string = json["bev"].string_value();
    unikey     = json["uni_key"].string_value();

    Json user_json_data = json["cli_data"];
    if(!user_json_data.is_object())
    {
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "do_worker err: cli_data is not a json object\n";
        string err = R"({"action":"login", "status":"error", "what":"server error."})";
        string e;
        Json err_json = Json::parse(err, e);

        err_json = Json::object({{"cli_data", err_json}, {"bev", bev_string}});
        return err_json.dump();
    }

    type = user_json_data["action"].int_value();

    /***
     *   logout
     */
    if(type == 2) {
        user_id = user_json_data["user_id"].string_value();
        session = user_json_data["session"].string_value();

        Json j1 = Json::object({{"action", "logout"}, {"user_id", user_id},
                                {"session", session}, {"status", "ok"},
                               {"bev", bev_string}});
        write_data_to_cache_svr(j1.dump());
        return "";
    }
    /*** end logout */

    user_name = user_json_data["user_name"].string_value();
    user_pwd  = user_json_data["user_pwd"].string_value();

    try{
        sql::PreparedStatement *ps;
        ps = mysqlConn->prepareStatement("select user_id from mj_users where "
                            "user_name=? AND user_pwd=?");
        ps->setString(1, user_name);

        MD5 md5(user_pwd);
        std::string md5str = md5.md5();
        ps->setString(2, md5str);

        sql::ResultSet *res = ps->executeQuery();
        while(res->next()){
            user_id.append(res->getString("user_id"));
            cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "success." << res->getString("user_id") << endl;
        }
    }
    catch(sql::SQLException &e){
        cout << "[" << "event_handler.cpp" << ":" << __LINE__ << "] " << "do_worker err:" << e.getErrorCode() << ": " << e.what() << "\n";
        string err = R"({"action":"login", "status":"error", "what":"server error."})";
        string jse;
        Json err_json = Json::parse(err, jse);

        err_json = Json::object({{"cli_data", err_json}, {"bev", bev_string}});
        return err_json.dump();
    }

    if(user_id.empty())    {
        string err = R"({"action":"login", "status":"error", "what":"账号或密码错误"})";
        string e;
        Json err_json = Json::parse(err, e);

        err_json = Json::object({{"cli_data", err_json}, {"bev", bev_string}});
        return err_json.dump();
    }

    uuid_t uuid;
    uuid_generate(uuid);

    char ss_buf[64] = {0};
    int ret = ObjToHex(ss_buf, uuid, sizeof(uuid));
    if(ret != 0){
        string err = R"({"action":"login", "status":"error", "what":"server error."})";
        string e;
        Json err_json = Json::parse(err, e);

        err_json = Json::object({{"cli_data", err_json}, {"bev", bev_string}});
        return err_json.dump();
    }

    session = string(ss_buf);

    json = Json::object({{"action", "login"}, {"user_id", user_id},
                         {"session", session}, {"status", "ok"}});
    json = Json::object({{"cli_data", json}, {"bev", bev_string}, {"uni_key", unikey}});

    /***
     *   将数据保存到缓存中
     */
    {
        Json j1 = Json::object({{"action", "login"}, {"user_id", user_id},
                                {"session", session}, {"status", "ok"},
                               {"bev", bev_string}});
        write_data_to_cache_svr(j1.dump());
    }

    /***
     *   返回结果
     */
    return json.dump();
}
