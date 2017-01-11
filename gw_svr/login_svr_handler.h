#ifndef LOGIN_SVR_HANDLER_H
#define LOGIN_SVR_HANDLER_H


/***
 *  @base: event_base* base;
 */
void init_login_svr(void *base, void (*recv_cb)(const char *));

void write_data_to_login_svr(const char *data);

#endif // LOGIN_SVR_HANDLER_H
