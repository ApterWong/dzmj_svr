#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "stdafx.h"


void do_accept(struct evconnlistener *, evutil_socket_t,
               struct sockaddr *, int socklen, void *);

void do_signal(evutil_socket_t, short, void *);

void do_connect_read(struct bufferevent *bev, void *arg);

void do_connect_write(struct bufferevent *bev, void *arg);

void do_connect_error(struct bufferevent *bev, short event, void *arg);

#endif // EVENT_HANDLER_H
