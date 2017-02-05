#ifndef USER_DATA_OBJECT_H
#define USER_DATA_OBJECT_H

#include <memory>
using namespace std;

struct other_user_data_object_t
{
    int id;
    int gpc_seq[8];//杠碰吃 顺序
    int gpc_seq_count;
    int paiCount;
    int paiRecCount;
    int _g;
    int _p;
    int _c;

    char chi[16];
    char gang[8];
    char peng[8];
    char NewCard;
};

struct user_data_object_t
{
    user_data_object_t();

    uint64_t user_id;
    uint64_t desk_id;

    int self_id;//0-3 玩家座位号（方位）

    int gpc_seq[8];//杠碰吃 顺序
    int gpc_seq_count;
    int paiCount;
    int paiRecCount;
    int _g;
    int _p;
    int _c;

    int cHuCount;
    int cPengCount;
    int cGangCount;
    int cChiCount;

    char paiRecList[36];
    char paiList[16];
    char chi[16];
    char gang[8];
    char peng[8];

    char cHuList[16];
    char cChiList[16];
    char cGangList[8];
    char cPengList[8];

    char NewCard;
    char wang;
};

using user_data_object = shared_ptr<user_data_object_t>;

user_data_object user_data_object_new();

std::string user_data_to_hex(user_data_object &obj);
std::string other_user_data_to_hex(user_data_object &obj);


class user_data_process
{
public:
    user_data_process();
    ~user_data_process();

    void set_user_data_object(user_data_object &obj);
    user_data_object get_user_data_object()const;

    int chupai(const char card);
    int test_chi(const char card);
    int test_peng(const char card);
    int test_gang(const char card);
    int test_hu(const char card);

    void setHu_list(const char *hu, int hc);
    void setGang_list(const char *gang, int hc);
    void setPeng_list(const char *peng, int hc);
    void setChi_list(const char *chi, int hc);
private:
    user_data_object obj;
};

#endif // USER_DATA_OBJECT_H
