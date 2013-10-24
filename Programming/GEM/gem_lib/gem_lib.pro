TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    Commons.hpp \
    Geometry/PrimitiveGeometry.hpp \
    Geometry/ComplexGeometry.hpp \
    Painter/Painter.hpp \
    Geometry/Geometry.hpp \
    Painter/Scene.hpp \
    Painter/Drawable.hpp \
    Geometry/Utils.hpp

cache()
