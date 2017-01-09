LIBS += -lr3c -levent -ljson11 -lhiredis

CONFIG += c++11

TARGET = cache_svr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    stdafx.cpp \
    event_handler.cpp \
    abstract_redis_operator.cpp \
    redis_instance.cpp \
    login_operator.cpp \
    bev_manager.cpp \
    logout_operator.cpp

HEADERS += \
    stdafx.h \
    event_handler.h \
    abstract_redis_operator.h \
    redis_instance.h \
    login_operator.h \
    bev_manager.h \
    logout_operator.h
