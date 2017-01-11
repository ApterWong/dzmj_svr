#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <signal.h>

#include "event_handler.h"
#include "cache_svr_handler.h"

#define PORT 8001

using namespace std;
using namespace sql;
Connection *mysqlConn;

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *ev_signal;

    base = event_base_new();

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    /* connect to mysql */
    sql::mysql::MySQL_Driver *driver;
    try{
        driver = sql::mysql::get_mysql_driver_instance();

        mysqlConn = driver->connect("tcp://127.0.0.1:3306", "dzmj", "123456");

        if (!mysqlConn->isValid())
        {
            std::cout << "Connect to MySQL Server failed!" << std::endl;
            return -1;
        }
        mysqlConn->setSchema("dzmj");
    }
    catch(sql::SQLException &e)
    {
        cout << e.what() << endl;
        exit(-1);
    }

    // listen new connect
    listener = evconnlistener_new_bind(base, do_accept, base, LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,
                                       -1, (sockaddr*)(&addr), sizeof(addr));

    // new signal event
    ev_signal = evsignal_new(base, SIGINT, do_signal, (void *)base);

    // connect to cache svr
    init_cache_svr(base, NULL);

    printf("login server start at port: %d...\n", PORT);

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(ev_signal);
    event_base_free(base);
    mysqlConn->close();

    printf("done\n");
}
