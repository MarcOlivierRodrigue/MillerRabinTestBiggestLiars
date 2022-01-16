cmake_minimum_required(VERSION 3.22) 
project(MillerRabinTest)              
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(MillerRabinTest ${SOURCE_FILES})

find_package(OpenMP REQUIRED)
target_link_libraries(MillerRabinTest PRIVATE OpenMP::OpenMP_CXX)