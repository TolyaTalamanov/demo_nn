cmake_minimum_required(VERSION 3.5)
project(demo_nn)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GUI_INCLUDE gui/mainwindow.h)
set(GUI_SOURCE gui/mainwindow.cpp)

find_package(Qt5Widgets REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

qt5_use_modules(${PROJECT_NAME} Widgets)

