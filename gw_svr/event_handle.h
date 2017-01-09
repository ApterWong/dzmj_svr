#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "stdafx.h"

// 处理客户端发来的消息
void do_accept(struct evconnlistener *, evutil_socket_t,
               struct sockaddr *, int socklen, void *);

void do_signal(evutil_socket_t, short, void *arg);

void do_connect_read(struct bufferevent *bev, void *);

void do_connect_write(struct bufferevent *bev, void *arg);

void do_connect_error(struct bufferevent *bev, short event, void *);

// 处理login_svr发来的消息
void do_login_recv(const char *buf);

// 处理worker_svr发来的消息
void do_worker_recv(const char *buf);

// 处理cache_svr发来的消息
void do_cache_recv(const char *buf);

#endif // EVENT_HANDLER_H
