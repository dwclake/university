# Project info
cmake_minimum_required( VERSION 3.22.1 )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

project( assignment1 LANGUAGES CXX )

# Files and Libs
set( SOURCE src )
set( INCLUDE src )

set( INCLUDES )

set( SOURCES )

set( LIBRARIES )

# Executables
add_executable( assignment1 ${SOURCE}/main.cpp ${INCLUDES} ${SOURCES} )
target_link_libraries( assignment1 PRIVATE ${LIBRARIES} )
