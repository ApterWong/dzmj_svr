#include "room_data2json.h"

room_data2Json::room_data2Json()
    :valid(false)
{

}

void room_data2Json::setObject(room_data_object &obj)
{
    this->data = obj;
    this->valid = true;
}

Json room_data2Json::getRoomJsonData()
{
    Json json = Json::object({
                                 {"zhuang_id", data->zhuang_id},
                                 {"napai_fangxiang", data->napai_fangxiang},
                                 {"cur_id", data->cur_id},
                                 {"wait", data->f_hgpc_wait},
                                 {"pai_Count", data->pai_Count},
                                 {"max_pai_count", data->max_pai_count},
                                 {"next_bupai", data->next_bupai},
                                 {"xw_card", data->xw_card},
                                 {"wang", data->wang}
                             });

    return json;
}

