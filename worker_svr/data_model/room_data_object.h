#ifndef ROOM_DATA_OBJECT_H
#define ROOM_DATA_OBJECT_H

#include <memory>
using namespace std;

using uchar = unsigned char;

struct room_data_object_t
{
    room_data_object_t();

    uint64_t desk_id;
    int user_id[4];

    int zhuang_id;
    int winner_id;
    int napai_fangxiang;//抓牌方向, 默认从庄家处顺时针数两个色子和的大小定位,
                        //从抓牌方位的上家牌堆数色子和*2翻牌+1为王
    int cur_id;
    int f_gang;
    int f_fgpc_valid;
    int f_hgpc_wait; // 1 is wait, 有些操作就会无效

    int players_plocy[4];
    int curr_plocy;
    int curr_plocy_id;

    int pai_Count;//当前牌数，
    int max_pai_count;//当局最多能有几张牌
    int next_bupai;//下一张补牌牌位

    //1,2抓牌时定方位，　3,4定王
    char saizi1, saizi2;//, saizi3, saizi4;
    char xw_card;

    char pailist[136];//所有的牌
    char wang;
    char last_card;
    char timeout_card;
    char last_chi[4];
    char timeout_id;
};

typedef shared_ptr<room_data_object_t> room_data_object;

room_data_object room_data_object_new();

#endif // ROOM_DATA_OBJECT_H
