cmake_minimum_required(VERSION 3.5)

add_definitions(-DCPU_ONLY=1)
add_definitions(-DUSE_OPENCV=ON)
add_definitions(-std=c++14)

project(demo_nn)

set(LIBRARY DetectorLib)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(GUI_INCLUDE gui/mainwindow.hpp)
set(GUI_SOURCE gui/mainwindow.cpp)

find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Caffe REQUIRED)

add_library(${LIBRARY} SHARED detector/detector.hpp
                             	detector/detector.cpp
	                            detector/label_parser.hpp
															detector/label_parser.cpp)

include_directories(detector ${Caffe_INCLUDE_DIRS})
target_link_libraries(${LIBRARY} ${Caffe_LIBRARIES} ${OpenCV_LIBS})

add_executable(sample_detect detector/sample_detect.cpp)
target_link_libraries(sample_detect ${LIBRARY})

add_executable(${PROJECT_NAME} demo_nn.cpp ${GUI_INCLUDE} ${GUI_SOURCE})

qt5_use_modules(${PROJECT_NAME} Widgets)
