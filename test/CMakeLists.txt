
cmake_minimum_required(VERSION 3.8)
project(rainboy_algorithms_tests CXX)
set (CMAKE_CXX_STANDARD 20)

include_directories(../include)


include(CheckIncludeFileCXX)
set(CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR})
CHECK_INCLUDE_FILE_CXX(catch_amalgamated.hpp _has_catch)
if(NOT "${_has_catch}")
	message("WARNING: catch.hpp not found, run ./download_catch.sh from test/ directory first")
endif()


file(GLOB test_sources RELATIVE ${PROJECT_SOURCE_DIR} "test_*.cpp")
add_library(catch2 catch_amalgamated.cpp)


foreach(_source_cpp ${test_sources})
	get_filename_component(_name_without_extension "${_source_cpp}" NAME_WE)
	add_executable(${_name_without_extension} ${_source_cpp})
    target_link_libraries(${_name_without_extension} catch2)
endforeach()
#
# add_executable(test_all ${test_sources} $<TARGET_OBJECTS:catch_amalgamated>)
