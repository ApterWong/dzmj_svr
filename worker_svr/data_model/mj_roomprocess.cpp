#include "mj_roomprocess.h"
#include "mj_util.h"

#include <cstring>
#include <algorithm>

const char *ROOM_KEY_PREFIX = "roomid:";
const char *USER_KEY_PREFIX = "userid:";

void mj_roomprocess::get_cchi_list(user_data_object &obj, char card, vector<string> &result)
{

}

mj_roomprocess::mj_roomprocess(std::string &id)
{
    this->room_id = id;
    this->load(); 
}

mj_roomprocess::~mj_roomprocess()
{
    this->store();
}

void mj_roomprocess::load()
{
    CRedisClient *rds = redis_instance::getInstance();

    string value;
    if( !rds->get(ROOM_KEY_PREFIX+this->room_id, &value) )
    {
        throw(1);//WARNING
        return ;
    }
    room_data_object_t *room_mem = new room_data_object_t();
    memcpy(room_mem, value.c_str(), value.size());
    this->room = room_data_object(room_mem);

    string user_id;
    for(int i=0; i<4; i++) {
        user_id = mj_util::mj_itoa(this->room->user_id[0]);
        if( !rds->get(USER_KEY_PREFIX+user_id, &value) )
        {
            throw(2);//WARNING
            return ;
        }
        user_data_object_t *user_mem = new user_data_object_t();
        memcpy(user_mem, value.c_str(), value.size());
        this->players.emplace_back(user_data_object(user_mem));
    }
}

void mj_roomprocess::store()
{
    CRedisClient *rds = redis_instance::getInstance();

    string room_data((char*)this->room.get(), sizeof(this->room));
    rds->set(ROOM_KEY_PREFIX+this->room_id, room_data);

    string user_data, user_id;
    for(int i=0; i<4; i++) {
        user_id = mj_util::mj_itoa(this->players[i]->user_id);
        user_data.assign((char*)this->players[i].get(), sizeof(this->players[0]));
        rds->set(USER_KEY_PREFIX+user_id, user_data);
    }
}

string mj_roomprocess::new_game(vector<string> &users, room_data_object &roomdata, vector<user_data_object> &userdatas)
{
    auto room = room_data_object_new();

    string s_roomid = mj_util::create_roomname();
    uint64_t i_roomid;

    mj_util::mj_atoi(s_roomid, i_roomid);

    room->saizi1 = mj_util::create_saizi_number();
    room->saizi2 = mj_util::create_saizi_number();
    //room->saizi3 = mj_util::create_saizi_number();
    //room->saizi4 = mj_util::create_saizi_number();

    uint64_t userId;
    user_data_object obj;
    vector<user_data_object> userobjs;

    mj_util::mj_atoi(users[0], userId);
    room->user_id[0] = userId;
    obj = user_data_object_new();
    obj->self_id = 1;
    obj->user_id = userId;
    obj->desk_id = i_roomid;
    userobjs.push_back(obj);

    mj_util::mj_atoi(users[1], userId);
    room->user_id[1] = userId;
    obj = user_data_object_new();
    obj->self_id = 2;
    obj->user_id = userId;
    obj->desk_id = i_roomid;
    userobjs.push_back(obj);

    mj_util::mj_atoi(users[2], userId);
    room->user_id[2] = userId;
    obj = user_data_object_new();
    obj->self_id = 3;
    obj->user_id = userId;
    obj->desk_id = i_roomid;
    userobjs.push_back(obj);

    mj_util::mj_atoi(users[3], userId);
    room->user_id[3] = userId;
    obj = user_data_object_new();
    obj->self_id = 4;
    obj->user_id = userId;
    obj->desk_id = i_roomid;
    userobjs.push_back(obj);

    //
    room->desk_id = i_roomid;
    room->zhuang_id = 1;

    //洗牌
    srand(time(NULL));
    int cardCount[136] = {0};
    for(auto i=0; i<136; i++)
    {
        int r = rand() % 136;
        while(cardCount[r] != 0) r++, r %= 136;

        room->pailist[i] = mj_util::cardSet[r];
        cardCount[r] = 1;//标记已选
    }

    //发牌
    room->napai_fangxiang = max(room->saizi1, room->saizi2) % 4;
    room->max_pai_count = 136;
    room->next_bupai = 135;
    room->pai_Count = (room->saizi1 + room->saizi2) * 2;
    room->cur_id     = 1;//初始化为0,每次发牌时+1发牌．

    for(int i=0; i<13; i++) {
        userobjs[0]->paiList[i] = room->pailist[room->pai_Count++];
        userobjs[1]->paiList[i] = room->pailist[room->pai_Count++];
        userobjs[2]->paiList[i] = room->pailist[room->pai_Count++];
        userobjs[3]->paiList[i] = room->pailist[room->pai_Count++];
    }
    userobjs[0]->NewCard = room->pailist[room->pai_Count++];

    //选王
    int xw_saizi= (room->saizi1 + room->saizi2) * 2;
    room->max_pai_count -= xw_saizi;
    room->xw_card = room->pailist[room->max_pai_count];
    //room->max_pai_count -= 2;

    switch(room->xw_card)
    {
        case mj_util::MJ_JIUWAN:
            room->wang = mj_util::MJ_YIWAN;
            break;
        case mj_util::MJ_JIUTONG:
            room->wang = mj_util::MJ_YITONG;
            break;
        case mj_util::MJ_JIUTIAO:
            room->wang = mj_util::MJ_YITIAO;
            break;
        case mj_util::MJ_BAN:
            room->wang = mj_util::MJ_DONG;
            break;
        default:
            room->wang -= 1;//九万的ascii值比一万小
    }
    userobjs[0]->wang = room->wang;
    userobjs[1]->wang = room->wang;
    userobjs[2]->wang = room->wang;
    userobjs[3]->wang = room->wang;

    //保存数据
    {
        CRedisClient *rds = redis_instance::getInstance();

        string data;
        data.assign((char*)room.get(), sizeof(room_data_object_t));
        rds->set(ROOM_KEY_PREFIX+s_roomid, data);

        data.assign((char*)userobjs[0].get(), sizeof(user_data_object_t));
        rds->set(USER_KEY_PREFIX+users[0], data);

        data.assign((char*)userobjs[1].get(), sizeof(user_data_object_t));
        rds->set(USER_KEY_PREFIX+users[1], data);

        data.assign((char*)userobjs[2].get(), sizeof(user_data_object_t));
        rds->set(USER_KEY_PREFIX+users[2], data);

        data.assign((char*)userobjs[3].get(), sizeof(user_data_object_t));
        rds->set(USER_KEY_PREFIX+users[3], data);
    }

    roomdata  = std::move(room);
    userdatas = std::move(userobjs);

    return s_roomid;
}

/***
 *      发牌操作，发一张牌给摸牌玩家（通常是当前cur_id+1），牌数大于max_pai_count游戏结束
 *      @cur_id:输出参数，当前摸牌的玩家
 *      @card:	输出参数，摸到的牌是哪张（什么牌）
 *      return: error or success
 */
bool mj_roomprocess::fapai(int &cur_id, char &card)
{    
    this->room->cur_id += 1;
    if(this->room->cur_id > 4) this->room->cur_id = 1;

    if(this->room->pai_Count+1 > this->room->max_pai_count) {
        // game over!
        return false;
    }

    cur_id = this->room->cur_id;
    card   = this->room->pailist[this->room->pai_Count++];
    this->players[cur_id]->NewCard = card;

    return true;
}

bool mj_roomprocess::chupai(const string &uid, char card)
{
    uint64_t user_id;
    mj_util::mj_atoi(uid, user_id);

    int cur_id = -1;
    for(int i=0; i<4; i++) {
        if(user_id == (this->players[i])->user_id) {
            cur_id = (this->players[i])->self_id;
        }
    }
    if(cur_id < 1 || cur_id > 4) {
        cout << "[mj_roomprocess.cpp:" << __LINE__ << "]: players->self id err or not find.\n";
        return false;
    }

    //核对是否是该玩家出牌
    if(room->cur_id != cur_id) {
        cout << "[mj_roomprocess.cpp:" << __LINE__ << "]: room->cur_id err.\n";
        return false;
    }

    //出牌
    auto &userdata = this->players[cur_id + 1];
    if(userdata->NewCard == card) {
        this->players[cur_id+1]->NewCard = mj_util::MJ_OTHERNEWCARD;
    }
    else {
        int i=0;
        for(; i<userdata->paiCount; i++ ){
            if(card == userdata->paiList[i]) {
                userdata->paiList[i] = userdata->NewCard;
                std::sort(userdata->paiList, userdata->paiList+16, [](char a, char b){ return a<b; });//保证降序
            }
            if(i >= userdata->paiCount) {
                cout << "[mj_roomprocess.cpp:" << __LINE__ << "]: not find chupai card.\n";
                return false;
            }
        }
    }

    return true;
}

void mj_roomprocess::hint_hgpc(const string &uid, char card, vector<int> &h, vector<int> &g, vector<int> &p, vector<vector<string> > &c)
{
    uint64_t user_id;
    mj_util::mj_atoi(uid, user_id);

    for(int i=0; i<4; i++) {
        auto &userdata = this->players[i];

        if(user_id == userdata->user_id) {
            h.push_back(0);
            g.push_back(0);
            p.push_back(0);
            c.push_back(vector<string>());
            continue;
        }

        /***
         * 判断能胡
         */
        int j = 0;
        for(; j<userdata->cHuCount; j++) {
            if(card == userdata->cHuList[j]) {
                room->players_plocy[i] |= P_Hu;
                h.push_back(card);
            }
        }
        if(j >= userdata->cHuCount)
            h.push_back(0);

        /***
         * 判断能杠
         */
        j = 0;
        for(; j<userdata->cGangCount; j++) {
            if(card == userdata->cGangList[j]) {
                room->players_plocy[i] |= P_Gang;
                g.push_back(card);
            }
        }
        if(j >= userdata->cGangCount)
            g.push_back(0);

        /***
         * 判断能碰
         */
        j = 0;
        for(; j<userdata->cPengCount; j++) {
            if(card == userdata->cPengList[j]) {
                room->players_plocy[i] |= P_Peng;
                p.push_back(card);
            }
        }
        if(j >= userdata->cPengCount)
            p.push_back(0);

        /***
         * 判断能吃
         */
        vector<string> chilist;
        j = 0;
        for(; j<userdata->cChiCount; j++) {
            if(card == userdata->cChiList[j])
            {
                this->get_cchi_list(userdata, card, chilist);
            }
        }
        c.push_back(chilist);
    }
}
