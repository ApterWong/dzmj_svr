LIBS += -levent -ljson11 -lr3c -lhiredis -lmysqlcppconn -luuid

CONFIG += c++11

TARGET = worker_svr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    event_handler.cpp \
    cache_svr_handler.cpp \
    stdafx.cpp \
    requests/abstract_request.cpp \
    requests/ready_request.cpp \
    requests/tuoguan_request.cpp \
    requests/chupai_request.cpp \
    requests/hu_request.cpp \
    requests/gang_request.cpp \
    requests/zgang_request.cpp \
    requests/agang_request.cpp \
    requests/peng_request.cpp \
    requests/chi_request.cpp \
    data_model/room_data_object.cpp \
    redis_cli/redis_support.cpp \
    requests/gamestart_request.cpp \
    sql_cli.cpp \
    mj_util.cpp \
    data_convert.c \
    data_model/mj_dataprocess.cpp \
    data_model/mj_roomprocess.cpp \
    data_model/user_data_object.cpp \
    data_model/user_data2json.cpp \
    data_model/room_data2json.cpp \
    requests/requests_factory.cpp \
    timer_svr_handler.cpp \
    requests/timeout_request.cpp

HEADERS += \
    event_handler.h \
    cache_svr_handler.h \
    stdafx.h \
    requests/abstract_request.h \
    requests/ready_request.h \
    requests/tuoguan_request.h \
    requests/chupai_request.h \
    requests/hu_request.h \
    requests/gang_request.h \
    requests/zgang_request.h \
    requests/agang_request.h \
    requests/peng_request.h \
    requests/chi_request.h \
    data_model/room_data_object.h \
    redis_cli/redis_support.h \
    requests/gamestart_request.h \
    sql_cli.h \
    mj_util.h \
    data_convert.h \
    data_model/mj_dataprocess.h \
    data_model/mj_roomprocess.h \
    data_model/user_data_object.h \
    data_model/user_data2json.h \
    data_model/room_data2json.h \
    requests/requests_factory.h \
    timer_svr_handler.h \
    requests/timeout_request.h
