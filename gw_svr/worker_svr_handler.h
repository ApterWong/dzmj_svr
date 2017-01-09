#ifndef WORKER_SVR_HANDLER_H
#define WORKER_SVR_HANDLER_H

const char *WORKER_SVR_ADDRESS = "127.0.0.1";
const short int WORKER_SVR_PORT = 8002;

/***
 *  @base: event_base* base;
 */
void init_worker_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_worker_svr(const char *data);

#endif // WORKER_SVR_HANDLER_H
