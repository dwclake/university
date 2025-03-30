cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

project( lab1 )

set( HEADER_FILES Array.h )
set( SOURCE_FILES )

add_executable( lab1 lab1.cpp ${HEADER_FILES} )
