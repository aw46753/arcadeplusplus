cmake_minimum_required(VERSION 3.16)

project(arcadepp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE ARCADEPP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(arcadepp ${ARCADEPP_SOURCES})

target_include_directories(arcadepp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(arcadepp PRIVATE /W4)
else()
    target_compile_options(arcadepp PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# First try to find an installed raylib package
find_package(raylib CONFIG QUIET)

# If not found, download and build it
if(NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )

    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(arcadepp PRIVATE raylib)