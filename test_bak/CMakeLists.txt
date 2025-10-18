
cmake_minimum_required(VERSION 3.8)
project(rainboy_algorithms_tests CXX)
set(CMAKE_CXX_STANDARD 20)
set(Catch2_path ./catch2-v3.4.0)
message(${Catch2_path})

include_directories(../include)
include_directories(${Catch2_path})


include(CheckIncludeFileCXX)
set(CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR})
# CHECK_INCLUDE_FILE_CXX(catch_amalgamated.hpp _has_catch)

file(GLOB test_sources RELATIVE ${PROJECT_SOURCE_DIR} "test_*.cpp")
add_library(catch2 "${Catch2_path}/catch_amalgamated.cpp") # 这里有什么错误?


foreach(_source_cpp ${test_sources})
	get_filename_component(_name_without_extension "${_source_cpp}" NAME_WE)
	add_executable(${_name_without_extension} ${_source_cpp})
    target_link_libraries(${_name_without_extension} catch2)
endforeach()
#
# add_executable(test_all ${test_sources} $<TARGET_OBJECTS:catch_amalgamated>)
