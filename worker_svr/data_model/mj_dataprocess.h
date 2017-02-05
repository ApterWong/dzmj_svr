#ifndef MJ_DATAPROCESS_H
#define MJ_DATAPROCESS_H

#include "user_data_object.h"
#include "room_data_object.h"

class mj_dataprocess
{
public:
    mj_dataprocess();
    ~mj_dataprocess();

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

#endif // MJ_DATAPROCESS_H
