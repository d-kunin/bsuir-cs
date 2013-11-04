TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ConsolePainter.cpp

HEADERS += \
    ConsolePainter.hpp

QMAKE_CXXFLAGS += -std=c++0x

cache()
