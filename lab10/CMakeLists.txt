cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS on )
set( CMAKE_BUILD_TYPE Debug )

set( PROJECT lab10 )
project( ${PROJECT} )

set( HEADER_FILES Graph.h Queue.h )
set( SOURCE_FILES Graph.cpp )

add_executable( ${PROJECT} ${PROJECT}.cpp ${HEADER_FILES} ${SOURCE_FILES} )
