TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pthread
QMAKE_CXXFLAGS += -Wl,--no-as-needed
LIBS += -lpthread
SOURCES += main.cpp \
    netmsg.cpp \
    connection.cpp

HEADERS += \
    netmsg.h \
    connection.h
