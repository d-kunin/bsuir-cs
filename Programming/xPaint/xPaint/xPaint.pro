#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T16:53:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xPaint
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        xpaintwindow.cpp \
        paintwidget.cpp \
        gem_lib/Painter/qimagedrawable.cpp \
        Qt/Converts.cpp \
    io/textfileserializer.cpp \
    gem_lib/Painter/DrawableGeometry.cpp \
    gem_lib/Painter/Scene.cpp \
    gem_lib/Painter/Painter.cpp \
    gem_lib/Painter/Color.cpp

HEADERS  += xpaintwindow.hpp \
         paintwidget.hpp \
         gem_lib/Painter/Scene.hpp \
         gem_lib/Painter/Drawable.hpp \
         gem_lib/Painter/DrawableGeometry.hpp \
         gem_lib/Painter/Paint.hpp \
         gem_lib/Geometry/Geometry.hpp \
         gem_lib/Geometry/Transform.hpp \
         QxPainter.hpp \
         Tool.hpp \
         gem_lib/Geometry/Algorithm.hpp \
         gem_lib/Painter/qimagedrawable.hpp \
         Qt/Converts.hpp \
    io/Serializable.hpp \
    io/textfileserializer.hpp \
    io/Serializer.hpp \
    io/Deserializer.hpp

FORMS    += xpaintwindow.ui
