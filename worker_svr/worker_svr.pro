LIBS += -levent -ljson11 -lr3c -lhiredis

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
    data_model/user_data_object.cpp \
    redis_cli/redis_support.cpp

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
    data_model/user_data_object.h \
    redis_cli/redis_support.h
