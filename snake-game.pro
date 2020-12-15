TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

DISTFILES +=

HEADERS += \
    snake_func.h \
    init.h
LIBS += -lWinmm
