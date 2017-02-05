LIBS += -lr3c -levent -ljson11 -lhiredis

CONFIG += c++11

TARGET = cache_svr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    stdafx.cpp \
    event_handler.cpp \
    mj_util.cpp \
    data_convert.c \
    svr_management.cpp

HEADERS += \
    stdafx.h \
    event_handler.h \
    event_handler.h \
    mj_util.h \
    data_convert.h \
    svr_management.h
