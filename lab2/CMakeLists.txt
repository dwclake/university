cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

project( lab2 )

set( HEADER_FILES Array3D.h )
set( SOURCE_FILES )

add_executable( lab2 lab2.cpp ${HEADER_FILES} )
