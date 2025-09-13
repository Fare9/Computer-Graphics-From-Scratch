cmake_minimum_required(VERSION 3.15)
project(GraphicsFromScratch CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find raylib
set(RAYLIB_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../raylib-5.5_linux_amd64")

find_path(RAYLIB_INCLUDE_DIR
        NAMES raylib.h
        HINTS ${RAYLIB_ROOT_DIR}/include
)

# Force static library by looking for .a file specifically
find_library(RAYLIB_LIBRARY
        NAMES libraylib.a
        HINTS ${RAYLIB_ROOT_DIR}/lib
        NO_DEFAULT_PATH  # Only look in the specified path
)

# Fallback to other names if .a not found
if(NOT RAYLIB_LIBRARY)
    find_library(RAYLIB_LIBRARY
            NAMES raylib_static raylib libraylib
            HINTS ${RAYLIB_ROOT_DIR}/lib
    )
endif()

if(NOT RAYLIB_INCLUDE_DIR OR NOT RAYLIB_LIBRARY)
    message(FATAL_ERROR "Raylib not found! Extract raylib 5.5 to 'raylib/' folder.")
endif()

message(STATUS "Found raylib:")
message(STATUS "  Include: ${RAYLIB_INCLUDE_DIR}")
message(STATUS "  Library: ${RAYLIB_LIBRARY}")

# Create imported target for raylib
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${RAYLIB_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${RAYLIB_INCLUDE_DIR}
)

# Add our graphics library
add_subdirectory(lib)

# Create main executable
add_executable(graphics_from_scratch main.cpp)

# Link libraries - raylib handles everything internally!
target_link_libraries(graphics_from_scratch graphics_lib raylib)
target_include_directories(graphics_from_scratch PRIVATE include)