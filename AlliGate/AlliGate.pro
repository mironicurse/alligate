TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=gnu++14
QMAKE_CXXFLAGS += -pthread
QMAKE_CXXFLAGS += -Wl,--no-as-needed
QT -= core gui
LIBS += -lpthread

SOURCES += main.cpp\
    encryptor.cpp \
    protocol.cpp \
    netmsg.cpp \
    queuemanager.cpp \
    queuedispatcher.cpp \
    queueworker.cpp \
    storage.cpp \
    queuesendmsg.cpp \
    connection.cpp \
    tcpconnection.cpp \
    connblock.cpp \
    server.cpp \
    logger.cpp \
    baseautorization.cpp \
    metaqueue.cpp \
    tcpserver.cpp

HEADERS  += \
    encryptor.h \
    protocol.h \
    netmsg.h \
    queuemanager.h \
    queuedispatcher.h \
    queueworker.h \
    storage.h \
    queuesendmsg.h \
    connection.h \
    tcpconnection.h \
    connblock.h \
    server.h \
    logger.h \
    baseautorization.h \
    metaqueue.h \
    tcpserver.h \
    mainheader.h

