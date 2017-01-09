LIBS += -levent -luuid -lmysqlcppconn -ljson11

CONFIG += c++11

TARGET = login_svr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    event_handler.cpp \
    md5.cpp \
    data_convert.c \
    cache_svr_handler.cpp \
    stdafx.cpp

HEADERS += \
    event_handler.h \
    md5.h \
    data_convert.h \
    cache_svr_handler.h \
    stdafx.h
