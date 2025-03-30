cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS on )
set( CMAKE_BUILD_TYPE Debug )

set( PROJECT project )
project( ${PROJECT} )

set( DS src/ds )

set( HEADER_FILES ${DS}/array.h ${DS}/matrix.h  ${DS}/graph.h ${DS}/queue.h
                  src/world.h
                  src/entity.h
                )

set( SOURCE_FILES ${DS}/graph.cpp ${DS}/queue.cpp
                  src/entity.cpp
                )

add_executable( ${PROJECT} src/main.cpp ${HEADER_FILES} ${SOURCE_FILES} )
