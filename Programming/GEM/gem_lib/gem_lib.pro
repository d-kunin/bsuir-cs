TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    Commons.hpp \
    Geometry/PrimitiveGeometry.hpp \
    Geometry/ComplexGeometry.hpp \

cache()
