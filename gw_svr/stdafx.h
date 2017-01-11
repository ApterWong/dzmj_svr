#ifndef STDAFX_H
#define STDAFX_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>

typedef struct bufferevent * L_KEY;

extern std::map<std::string, L_KEY> map_userid2bev;
extern std::map<L_KEY, std::string> map_bev2userid;
extern std::map<L_KEY, std::string> map_bev2unikey;

extern struct bufferevent *g_loginserver_bev;


extern struct bufferevent *g_worker_bev;

#endif // STDAFX_H
