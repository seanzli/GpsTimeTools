cmake_minimum_required(VERSION 3.0.0)
project(GpsTimeTools VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)
include_directories(./Test)


# glog
find_package(glog 0.5.0 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lglog -lgflags -lpthread)
