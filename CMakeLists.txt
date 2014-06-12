cmake_minimum_required (VERSION 2.6)

project (FlashGraph)

# The version number.
set (FlashGraph_VERSION_MAJOR 0)
set (FlashGraph_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x" )
set(CMAKE_BUILD_TYPE Release)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}" include)

subdirs(libsafs utils flash-graph)