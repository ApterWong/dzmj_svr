#include "stdafx.h"

std::map<L_KEY, std::string> map_bev2userid;

struct bufferevent *g_loginserver_bev;

struct bufferevent *g_worker_bev;
