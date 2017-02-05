#ifndef GAMESTART_REQUEST_H
#define GAMESTART_REQUEST_H

#include "abstract_request.h"
#include "sql_cli.h"

/***
 * 此请求由游戏准备消息触发, 不是cli发送而来
 */
class gamestart_request : public abstract_request
{
public:
    gamestart_request(std::vector<string> &_users);

    string handler();
private:
    // 生成庄家id,
    // 查询user_name,
    //    > 返回players消息
    string analysis_playerinfo();

    //初始化一局游戏,
    //  > 返回gameinit消息
    string start_games();

    //给庄家发一张牌
    //  > 返回发牌消息(给庄家)
    string fapai();



private:

    vector<string> users;
};

#endif // GAMESTART_REQUEST_H
