cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

project( lab4 )

set( HEADER_FILES Array.h )
set( SOURCE_FILES )

add_executable( lab4 lab4.cpp ${HEADER_FILES} )
