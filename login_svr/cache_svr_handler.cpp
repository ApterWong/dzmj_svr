#include "cache_svr_handler.h"
#include "stdafx.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *CACHE_SVR_ADDRESS = "127.0.0.1";
const short int CACHE_SVR_PORT = 8003;

static struct bufferevent *g_cache_svr_bev;

static void (*handler_for_cache_recv)(const char *buf);
static void do_cache_read(bufferevent *bev, void *);
static void do_cache_write(bufferevent *bev, void *arg);
static void do_cache_error(bufferevent *bev, short event, void *);

void init_cache_svr(void *base, void (*recv_cb)(const char *))
{
    evutil_socket_t fd;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(CACHE_SVR_ADDRESS);
    addr.sin_port = htons(CACHE_SVR_PORT);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");
        exit(-1);
    }
    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
        perror("connect to cache server");
        exit(-1);
    }

    g_cache_svr_bev = bufferevent_socket_new ((struct event_base *)base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(NULL == g_cache_svr_bev) {
        perror("bufferevent_socket_new""memory out");
        exit(-1);
    }
    bufferevent_setcb (g_cache_svr_bev, do_cache_read, do_cache_write, do_cache_error, NULL);
    bufferevent_enable(g_cache_svr_bev, EV_READ|EV_WRITE);

    handler_for_cache_recv = recv_cb;

    // 发送身份识别信息
    const char *msg = R"({"server":"login"})";
    write_data_to_cache_svr(msg);
}

void write_data_to_cache_svr(string msg)
{
    struct evbuffer *out;

    out = bufferevent_get_output(g_cache_svr_bev);

    msg.append("\n");
    evbuffer_add(out, msg.c_str(), msg.length());
}

void do_cache_read(bufferevent *bev, void *)
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

        printf("recv from cache_svr %ld : %s\n", readlen, readbuf);
        printf("缺省处理程序\n");
        //handler_for_cache_recv(readbuf);

        free(readbuf);
    }
}

void do_cache_write(bufferevent *bev, void *arg)
{
    (void)(bev); (void)(arg);
}

void do_cache_error(bufferevent *bev, short event, void *)
{
    if(event & BEV_EVENT_EOF){
        printf("do_cache_error: %d is closed\n", bufferevent_getfd(bev));
    }
    else if(event & BEV_EVENT_ERROR) {
        printf("do_cache_error: %d has a error\n", bufferevent_getfd(bev));
        perror("do_cache_error");
    }

    bufferevent_free(bev);
}
