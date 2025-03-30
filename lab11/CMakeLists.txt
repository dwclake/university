cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS on )
set( CMAKE_BUILD_TYPE Debug )

set( PROJECT lab11 )
project( ${PROJECT} )

set( HEADER_FILES Matrix.h Fib.h)
set( SOURCE_FILES Matrix.cpp )

add_executable( ${PROJECT} ${PROJECT}.cpp ${HEADER_FILES} ${SOURCE_FILES} )
