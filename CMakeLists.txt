cmake_minimum_required(VERSION 3.16)

project(arcadepp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE ARCADEPP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(arcade++ ${ARCADEPP_SOURCES})

target_include_directories(arcade++ PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_options(arcade++ PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

find_package(raylib QUIET)

if(raylib_FOUND)
    target_link_libraries(arcade++ PRIVATE raylib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)

    target_include_directories(arcade++ PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_directories(arcade++ PRIVATE ${RAYLIB_LIBRARY_DIRS})
    target_link_libraries(arcade++ PRIVATE ${RAYLIB_LIBRARIES})
    target_compile_options(arcade++ PRIVATE ${RAYLIB_CFLAGS_OTHER})
endif()
