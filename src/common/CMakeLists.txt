#common
cmake_minimum_required(VERSION 2.8)
project(SAM)

file(GLOB_RECURSE  COMMON_CPP "./*.cpp")
add_library ( common STATIC ${COMMON_CPP} )
TARGET_LINK_LIBRARIES( common pthread )
