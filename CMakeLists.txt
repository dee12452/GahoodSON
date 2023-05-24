cmake_minimum_required(VERSION 3.8)
project(GahoodSON)

include_directories(./include)
add_library(GahoodSON STATIC ./src/parse.c)

install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" 
	DESTINATION include
)
