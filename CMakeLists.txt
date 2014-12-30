cmake_minimum_required(VERSION 2.8)
project(feature_extractor)
find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(glcm glcm.cpp feature_extractor.cpp glcm_feature_extractor.cpp histo_util.cpp lbp_feature_extractor.cpp)
target_link_libraries(glcm ${OpenCV_LIBS})

add_executable(lbp lbp.cpp feature_extractor.cpp glcm_feature_extractor.cpp histo_util.cpp lbp_feature_extractor.cpp)
target_link_libraries(lbp ${OpenCV_LIBS})
