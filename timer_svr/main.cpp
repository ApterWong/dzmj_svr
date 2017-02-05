#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <signal.h>

#include "event_handler.h"
#include "stdafx.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *ev_signal;

    base = event_base_new();

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(TIMER_SVR_PORT);

    // listen new connect
    listener = evconnlistener_new_bind(base, do_accept, base, LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,
                                       -1, (sockaddr*)(&addr), sizeof(addr));

    // new signal event
    ev_signal = evsignal_new(base, SIGINT, do_signal, (void *)base);

    printf("timer server start at port: %d...\n", TIMER_SVR_PORT);
    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(ev_signal);
    event_base_free(base);

    printf("done\n");
}
