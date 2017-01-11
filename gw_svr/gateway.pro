LIBS += -levent -ljson11 -luuid

CONFIG += c++11

TARGET = gateway
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    event_handle.cpp \
    dispatcher.cpp \
    stdafx.cpp \
    mj_util.cpp \
    login_svr_handler.cpp \
    worker_svr_handler.cpp \
    cache_svr_handler.cpp \
    data_convert.c

HEADERS += \
    event_handle.h \
    stdafx.h \
    dispatcher.h \
    mj_util.h \
    login_svr_handler.h \
    worker_svr_handler.h \
    cache_svr_handler.h \
    data_convert.h
