#ifndef TIMER_SVR_HANDLER_H
#define TIMER_SVR_HANDLER_H

#include <string>
using namespace std;
/***
 *  @base: event_base* base;
 */
void init_timer_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_timer_svr(string msg);

#endif // TIMER_SVR_HANDLER_H
