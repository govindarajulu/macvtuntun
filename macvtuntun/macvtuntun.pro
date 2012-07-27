TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    tun.c \
    tcpudp.c

HEADERS += \
    tun.h \
    main.h \
    tcpudp.h

