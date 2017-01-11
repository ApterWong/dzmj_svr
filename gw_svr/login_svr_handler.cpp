#include "login_svr_handler.h"
#include "stdafx.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *LOGIN_SVR_ADDRESS = "127.0.0.1";
const short int LOGIN_SVR_PORT = 8001;

static struct bufferevent *g_login_svr_bev;

static void (*handler_for_login_recv)(const char *buf);
static void do_login_read(bufferevent *bev, void *arg);
static void do_login_write(bufferevent *bev, void *arg);
static void do_login_error(bufferevent *bev, short event, void *arg);

void init_login_svr(void *base, void (*recv_cb)(const char *buf))
{
    evutil_socket_t fd;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(LOGIN_SVR_ADDRESS);
    addr.sin_port = htons(LOGIN_SVR_PORT);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");
        exit(-1);
    }
    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
        perror("connect to login server");
        exit(-1);
    }

    g_login_svr_bev = bufferevent_socket_new ((struct event_base *)base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(NULL == g_login_svr_bev) {
        perror("bufferevent_socket_new""memory out");
        exit(-1);
    }
    bufferevent_setcb (g_login_svr_bev, do_login_read, do_login_write, do_login_error, NULL);
    bufferevent_enable(g_login_svr_bev, EV_READ|EV_WRITE);

    handler_for_login_recv = recv_cb;
}


void do_login_read(bufferevent *bev, void *arg)
{
    struct evbuffer *in/*, *out*/;

    in = bufferevent_get_input(bev);
    /*out = bufferevent_get_output(bev);*/

    char *readbuf;
    size_t readlen = 0;

    while(1){
        readbuf = evbuffer_readln(in, &readlen, EVBUFFER_EOL_ANY);
        if(NULL == readbuf) {
            break;
        }

        printf("recv from login_svr %ld : %s\n", readlen, readbuf);

        handler_for_login_recv(readbuf);

        free(readbuf);
    }
}

void do_login_write(bufferevent *bev, void *arg)
{
    (void)(bev); (void)(arg);
}

void do_login_error(bufferevent *bev, short event, void *arg)
{
    if(event & BEV_EVENT_EOF){
        printf("do_login_error: %d is closed\n", bufferevent_getfd(bev));
    }
    else if(event & BEV_EVENT_ERROR) {
        printf("do_login_error: %d has a error\n", bufferevent_getfd(bev));
        perror("do_login_error");
    }

    bufferevent_free(bev);
}

void write_data_to_login_svr(const char *data)
{
    struct evbuffer *out;

    out = bufferevent_get_output(g_login_svr_bev);

    evbuffer_add(out, data, strlen(data));
}
