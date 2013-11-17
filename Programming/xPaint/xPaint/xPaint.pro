#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T16:53:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xPaint
TEMPLATE = app


SOURCES += main.cpp\
        xpaintwindow.cpp \
        paintwidget.cpp \

HEADERS  += xpaintwindow.hpp \
         paintwidget.hpp \
         gem_lib/Painter/Scene.hpp \
         gem_lib/Painter/Drawable.hpp \
         gem_lib/Painter/DrawableGeometry.hpp \
         gem_lib/Painter/Paint.hpp \
         QxPainter.hpp \
         Tool.hpp

FORMS    += xpaintwindow.ui
