#include "user_data2json.h"
#include "../mj_util.h"

user_data2json::user_data2json()
{
    this->valid = false;
}

void user_data2json::setObject(user_data_object &obj)
{
    this->data = obj;
    this->valid = true;
}

Json user_data2json::getUserJsonData()
{
    if(!this->valid)
        return nullptr;

    Json::array gpcarr;
    for(int i=0; i<data->gpc_seq_count; ++i) {
        gpcarr.push_back(data->gpc_seq[i]);
    }

    Json json = Json::object({
                 {"user_id", mj_util::mj_itoa(data->user_id)},
                 {"desk_id", mj_util::mj_itoa(data->desk_id)},
                 {"self_id", data->self_id},
                 {"gpc_seq", gpcarr},
                 {"gpc_seq_count", data->gpc_seq_count},
                 {"paiCount", data->paiCount},
                 {"paiRecCount", data->paiRecCount},
                 {"_g", data->_g},
                 {"_ag", data->_ag},
                 {"_p", data->_p},
                 {"_c", data->_c},
                 {"cHuCount", data->cHuCount},
                 {"cPengCount", data->cPengCount},
                 {"cGangCount",data->cGangCount},
                 {"cChiCount", data->cChiCount},
                 {"paiRecList", string(data->paiRecList)},
                 {"paiList", string(data->paiList)},
                 {"chi", string(data->chi)},
                 {"gang", string(data->gang)},
                 {"peng",string(data->peng)},
                 {"cHuList", string(data->cHuList)},
                 {"cChiList", string(data->cChiList)},
                 {"cGangList", string(data->cGangList)},
                 {"cPengList", string(data->cPengList)},
                 {"NewCard", data->NewCard},
                 {"wang", data->wang}
                             });

    return json;
}

Json user_data2json::getOtherUserJsonData()
{
    Json::array gpcarr;
    for(int i=0; i<data->gpc_seq_count; ++i) {
        gpcarr.push_back(data->gpc_seq[i]);
    }

    Json json = Json::object({
                 //{"user_id", mj_util::mj_itoa(data->user_id)},
                 //{"desk_id", mj_util::mj_itoa(data->desk_id)},
                 {"id", data->self_id},//{"self_id", data->self_id},
                 {"gpc_seq", gpcarr},
                 {"gpc_seq_count", data->gpc_seq_count},
                 {"paiCount", data->paiCount},
                 {"paiRecCount", data->paiRecCount},
                 {"_g", data->_g},
                 {"_ag", data->_ag},
                 {"_p", data->_p},
                 {"_c", data->_c},
                 //{"cHuCount", cHuCount},
                 //{"cPengCount", cPengCount},
                 //{"cGangCount",cGangCount},
                 //{"cChiCount", cChiCount},
                 {"paiRecList", string(data->paiRecList)},
                 //{"paiList", string(data->paiList)},
                 {"chi", string(data->chi)},
                 {"gang", string(data->gang)},
                 {"peng",string(data->peng)},
                 //{"cHuList", string(data->cHuList)},
                 //{"cChiList", string(data->cChiList)},
                 //{"cGangList", string(data->cGangList)},
                 //{"cPengList", string(data->cPengList)},
                 //{"wang", data->wang}
                 {"NewCard", mj_util::MJ_OTHERNEWCARD}
                             });

    return json;
}
