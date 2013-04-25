#STATION
cmake_minimum_required(VERSION 2.8)
project(SAM)

file(GLOB_RECURSE  NODE_CPP "./*.cpp")
ADD_EXECUTABLE( node ${NODE_CPP}  )

TARGET_LINK_LIBRARIES( node common )

