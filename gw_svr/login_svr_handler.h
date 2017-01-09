#ifndef LOGIN_SVR_HANDLER_H
#define LOGIN_SVR_HANDLER_H

const char *LOGIN_SVR_ADDRESS = "127.0.0.1";
const short int LOGIN_SVR_PORT = 8001;

/***
 *  @base: event_base* base;
 */
void init_login_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_login_svr(const char *data);

#endif // LOGIN_SVR_HANDLER_H
