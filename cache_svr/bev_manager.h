#ifndef BEV_MANAGER_H
#define BEV_MANAGER_H

#include <string>
using namespace std;

//extern struct bufferevent *gateway_bev;
//extern struct bufferevent *worker_bev;
//extern struct bufferevent *login_bev;

void set_gateway_bev(struct bufferevent *);
void set_worker_bev(struct bufferevent *);
void set_login_bev(struct bufferevent *);

void write_data_to_worker(string &msg);
void write_data_to_gateway(string &msg);
void write_data_to_login(string &msg);

#endif // BEV_MANAGER_H
