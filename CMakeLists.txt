cmake_minimum_required(VERSION 3.5)
add_definitions(-DCPU_ONLY=1)
add_definitions(-DUSE_OPENCV=ON)
project(demo_nn)

set(LIBRARY DetectorLib)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GUI_INCLUDE gui/mainwindow.h)
set(GUI_SOURCE gui/mainwindow.cpp)

find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Caffe REQUIRED)

add_library(${LIBRARY} STATIC detector/detector.h detector/detector.h)
include_directories(detector)

add_executable(${PROJECT_NAME} demo_nn.cpp ${GUI_INCLUDE} ${GUI_SOURCE})
include_directories(${Caffe_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Caffe_LIBRARIES})

qt5_use_modules(${PROJECT_NAME} Widgets)

add_subdirectory(sample)

