cmake_minimum_required(VERSION 3.6)
project(Snake CXX)
set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE sources src/*.cpp include/*.hpp)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -g -O0 -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wpointer-arith -Wwrite-strings -Wno-unknown-warning-option)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DDEBUG -D_DEBUG)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -O3)
	target_compile_options(${PROJECT_NAME} PRIVATE -march=native -Ofast -fopenmp -fno-math-errno)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DNDEBUG)
endif()

