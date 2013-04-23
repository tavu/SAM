#STATION
cmake_minimum_required(VERSION 2.8)
project(SAM)

file(GLOB_RECURSE  STATION_CPP "./*.cpp")
ADD_EXECUTABLE( station ${STATION_CPP}  )

TARGET_LINK_LIBRARIES( station pcap )
TARGET_LINK_LIBRARIES( station common )

