#ifndef DISPATCHER_H
#define DISPATCHER_H

enum Action_types
{
    action_login = 1,
    action_logout,
    action_cmd
};

void dispatch_command(const char *data, void *bev_address);

#endif // DISPATCHER_H
