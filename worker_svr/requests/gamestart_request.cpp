#include "gamestart_request.h"
#include "timer_svr_handler.h"
#include "mj_util.h"

#include "data_model/mj_roomprocess.h"
#include "data_model/mj_dataprocess.h"
#include "data_model/room_data2json.h"
#include "data_model/user_data2json.h"

gamestart_request::gamestart_request(std::vector<string> &_users)
    : users(std::move(_users))
{
    std::cout << "gamestart_request.cpp [" << __LINE__ << "] 执行完成.\n";
}

string gamestart_request::handler()
{
    cout << "gamestart_request.cpp [" << __LINE__ << "] handler 开始\n";
    //查询user_name,
    //    > 返回players消息
    //初始化一局游戏,
    //    > 返回gameinit消息
    //给庄家发一张牌
    //    > 返回发牌消息(给庄家)

    string result(4096, 0);

    try{
        result.append( analysis_playerinfo());
        result.append("\n");

        result.append(this->start_games());
        //result.append("\n");

        //result.append(this->fapai());
    }
    catch(sql::SQLException &e){
        cout << e.what() << "\n";
    }
    catch(...) {
        cout << "gamestart_request.cpp [" << __LINE__ << "] 未知错误\n";
    }


    cout << "gamestart_request.cpp [" << __LINE__ << "] handler 结束\n";
    return result;
}

string gamestart_request::analysis_playerinfo()
{

    vector<string> user_names;
    vector<int> user_scores;

    sql::PreparedStatement * ps;
    ps = mysqlConn->prepareStatement(
                "select u.user_name, d.score from mj_users as u join mj_userdata as d"
                " on u.user_id = d.user_id"
                " where u.user_id in (?,?,?,?)"
                );
    for(int i=0;i<4; i++)
        ps->setString(i+1, users[i]);

    auto result = ps->executeQuery();

    while(result->next()) {
        user_names.push_back(result->getString("user_name"));
        user_scores.push_back(result->getInt("score"));
    }

    //> 返回players消息
    Json::array info_arr;
    Json::array user_arr;
    for(int i=0; i<4; i++) {
        Json j = Json::object({{"id", i+1}, {"user_id", users[i]}, {"user_name", user_names[i]}, {"score", user_scores[i]}});
        info_arr.push_back(j);
        user_arr.push_back(users[i]);
    }
    Json json = Json::object({{"zhuangid", 1}, {"usersinfo", info_arr}, {"type", "game"},
                              {"cmd", "players"}, {"status", "ok"}});
    json = Json::object({{"cli_data", json}, {"user_id", user_arr}});

    return json.dump();
}

string gamestart_request::start_games()
{
    string result;
    room_data_object room;
    vector<user_data_object> userobjs;

    string roomid = mj_roomprocess::new_game(this->users, room, userobjs);


    Json::array user_arr;
    for(int i=0; i<4; i++) {
        user_arr.push_back(this->users[i]);
    }
    //抓牌色子
    {
        Json json = Json::object({{"type", "game"}, {"cmd", "zhuapai_saizi"}, {"status", "ok"},
                                  {"zhuapai_saizi", Json::array({room->saizi1, room->saizi2})}});
        json = Json::object({ {"cli_data", json}, {"user_id", user_arr} });

        result += json.dump();
        result += "\n";
    }
    //init_数据
    {
        room_data2Json room_converter;
        room_converter.setObject(room);
        Json room_json = room_converter.getRoomJsonData();

        user_data2json user_converter;
        user_converter.setObject(userobjs[0]);
        Json user1_json = user_converter.getUserJsonData();
        Json user1_json_other = user_converter.getOtherUserJsonData();

        user_converter.setObject(userobjs[1]);
        Json user2_json = user_converter.getUserJsonData();
        Json user2_json_other = user_converter.getOtherUserJsonData();

        user_converter.setObject(userobjs[2]);
        Json user3_json = user_converter.getUserJsonData();
        Json user3_json_other = user_converter.getOtherUserJsonData();

        user_converter.setObject(userobjs[3]);
        Json user4_json = user_converter.getUserJsonData();
        Json user4_json_other = user_converter.getOtherUserJsonData();

        /***
         *      此json包含本桌数据，玩家对其玩家可见数据．
         * 发送给本桌所有的玩家（重复了自己的部分,
         * 自己的真实数据在后面一个json中发送）
         */
        Json gameinit_json = Json::object({
                                              {"1", user1_json_other},
                                              {"2", user2_json_other},
                                              {"3", user3_json_other},
                                              {"4", user4_json_other},
                                              {"room", room_json}
                                          });
        Json json = Json::object({{"type", "game"}, {"cmd", "gameinit"}, {"status", "ok"},
                                  {"gameinit", gameinit_json}
                                 });
        json = Json::object({ {"cli_data", json}, {"user_id", user_arr} });

        result += json.dump();
        result += "\n";

        /***
         *      发送玩家真实数据
         */
        json = Json::object({
                                {"1", user1_json}
                            });
        json = Json::object({{"type", "game"}, {"cmd", "gameinit"}, {"status", "ok"},
                                          {"gameinit", json}
                                         });
        json = Json::object({ {"cli_data", json}, {"user_id", this->users[0]} });

        result += json.dump();
        result += "\n";

        json = Json::object({
                                {"2", user2_json}
                            });
        json = Json::object({{"type", "game"}, {"cmd", "gameinit"}, {"status", "ok"},
                                          {"gameinit", json}
                                         });
        json = Json::object({ {"cli_data", json}, {"user_id", this->users[1]} });

        result += json.dump();
        result += "\n";

        json = Json::object({
                                {"3", user3_json}
                            });
        json = Json::object({{"type", "game"}, {"cmd", "gameinit"}, {"status", "ok"},
                                          {"gameinit", json}
                                         });
        json = Json::object({ {"cli_data", json}, {"user_id", this->users[2]} });

        result += json.dump();
        result += "\n";

        json = Json::object({
                                {"4", user4_json}
                            });
        json = Json::object({{"type", "game"}, {"cmd", "gameinit"}, {"status", "ok"},
                                          {"gameinit", json}
                                         });
        json = Json::object({ {"cli_data", json}, {"user_id", this->users[3]} });

        result += json.dump();
        result += "\n";
    }


    /***
     *      不存在定王色子
     */
//    //定王色子
//    {
//        Json json = Json::object({{"type", "game"}, {"cmd", "dingwan_saizi"}, {"status", "ok"},
//                                  {"dingwan_saizi", Json::array({room->saizi3, room->saizi4})}});
//        json = Json::object({ {"cli_data", json}, {"user_id", user_arr} });

//        result += json.dump();
//        result += "\n";
//    }

    // 发牌
    {
        // 发送给摸牌玩家的数据
        Json json = Json::object({
                                     {"id", 1},
                                     {"card", userobjs[0]->NewCard}
                                 });
        json = Json::object({
                                {"type", "game"}, {"cmd", "fapai"}, {"status", "ok"},
                                {"fapai", json}
                            });
        json = Json::object({
                                {"cli_data", json},
                                {"user_id", this->users[0]}
                            });
        result += json.dump();
        result += "\n";

        //发送给所有其他玩家的数据
        json = Json::object({
                                     {"id", 1},
                                     {"card", mj_util::MJ_OTHERNEWCARD}
                                 });
        json = Json::object({
                                {"type", "game"}, {"cmd", "fapai"}, {"status", "ok"},
                                {"fapai", json}
                            });
        json = Json::object({
                                {"cli_data", json},
                                {"user_id", user_arr}
                            });
        result += json.dump();
    }

    // 开始定时
    {
        Json tmjson = Json::object({
                                       {"roomid", roomid},
                                       {"timeval", 15000}, // 15s
                                       {"count", room->timeout_id}
                                   });
        write_data_to_timer_svr(tmjson.dump());
    }

    return result;
}

string gamestart_request::fapai()
{

}
