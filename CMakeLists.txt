cmake_minimum_required(VERSION 3.5)
project(demo_nn)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GUI_INCLUDE gui/mainwindow.h)
set(GUI_SOURCE gui/mainwindow.cpp)

find_package(Qt5Widgets REQUIRED)
find_package(Caffe REQUIRED)

add_executable(${PROJECT_NAME} demo_nn.cpp ${GUI_INCLUDE} ${GUI_SOURCE})
include_directories(${Caffe_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Caffe_LIBRARIES})

qt5_use_modules(${PROJECT_NAME} Widgets)

