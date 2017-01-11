#ifndef CACHE_SVR_HANDLER_H
#define CACHE_SVR_HANDLER_H

#include <string>
using namespace std;
/***
 *  @base: event_base* base;
 */
void init_cache_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_cache_svr(string msg);

#endif // CACHE_SVR_HANDLER_H
