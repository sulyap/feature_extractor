cmake_minimum_required(VERSION 2.8)
project(feature_extractor)
find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(feature_extractor main.cpp feature_extractor.cpp glcm_feature_extractor.cpp histo_util.cpp lbp_feature_extractor.cpp)
target_link_libraries(feature_extractor ${OpenCV_LIBS})
