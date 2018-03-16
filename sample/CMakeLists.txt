add_executable(sample_caffe sample_caffe.cpp)
target_link_libraries(sample_caffe ${Caffe_LIBRARIES} ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})
