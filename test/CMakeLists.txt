cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS on )

set( PROJECT test )
project( ${PROJECT} )

set( HEADER_FILES )
set( SOURCE_FILES )

add_executable( ${PROJECT} ${PROJECT}.cpp ${HEADER_FILES} )
