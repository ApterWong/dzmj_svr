#ifndef WORKER_SVR_HANDLER_H
#define WORKER_SVR_HANDLER_H

/***
 *  @base: event_base* base;
 */
void init_worker_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_worker_svr(const char *data);

#endif // WORKER_SVR_HANDLER_H
