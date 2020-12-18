cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(testassimp)

set(CMAKE_CXX_STANDARD 17)
include_directories(include ext)
aux_source_directory(src SRC_LIST)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${OpenMP_C_FLAGS}")
    message("find openmp")
endif()

find_package(embree 3.0 REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(testassimp ${SRC_LIST} )
target_link_libraries(testassimp PRIVATE assimp::assimp Eigen3::Eigen embree OpenMP::OpenMP_CXX)

