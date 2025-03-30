cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS on )

set( PROJECT lab9 )
project( ${PROJECT} )

set( HEADER_FILES Bst.h )
set( SOURCE_FILES )

add_executable( ${PROJECT} ${PROJECT}.cpp ${HEADER_FILES} ${SOURCE_FILES} )
