#GLOBAL
cmake_minimum_required(VERSION 2.8)
project(SAM)

INCLUDE_DIRECTORIES(./src/common/)
ADD_DEFINITIONS( -Wall -Wno-reorder -lpthread -ggdb)


# subdirs(src/node)
subdirs(src/station)
subdirs(src/node)
subdirs(src/common)
