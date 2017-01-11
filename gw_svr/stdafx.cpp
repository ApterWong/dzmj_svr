#include "stdafx.h"

std::map<L_KEY, std::string> map_bev2userid;
std::map<std::string, L_KEY> map_userid2bev;
std::map<L_KEY, std::string> map_bev2unikey;

struct bufferevent *g_loginserver_bev;

struct bufferevent *g_worker_bev;
