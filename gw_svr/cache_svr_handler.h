#ifndef CACHE_SVR_HANDLER_H
#define CACHE_SVR_HANDLER_H

const char *CACHE_SVR_ADDRESS = "127.0.0.1";
const short int CACHE_SVR_PORT = 8003;

/***
 *  @base: event_base* base;
 */
void init_cache_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_cache_svr(const char *data);

#endif // CACHE_SVR_HANDLER_H
