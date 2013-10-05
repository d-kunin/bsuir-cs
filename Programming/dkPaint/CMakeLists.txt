cmake_minimum_required(VERSION 2.8)
project(XPaint)

set(SOURCE
    main.cpp
)

set(HEADERS
    xmath/matrix.hpp
    xmath/geometry.hpp
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(XPaint ${SOURCE} ${HEADERS})

