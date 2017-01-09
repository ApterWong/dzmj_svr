#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>

#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <uuid/uuid.h>
#include "md5.h"

extern sql::Connection *mysqlConn;

void do_accept(struct evconnlistener *, evutil_socket_t,
               struct sockaddr *, int socklen, void *);

void do_signal(evutil_socket_t, short, void *);

void do_connect_read(struct bufferevent *bev, void *arg);

void do_connect_write(struct bufferevent *bev, void *arg);

void do_connect_error(struct bufferevent *bev, short event, void *arg);

#endif // EVENT_HANDLER_H
