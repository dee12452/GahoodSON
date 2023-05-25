cmake_minimum_required(VERSION 3.8)
project(GahoodSON)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(GahoodSON STATIC ${PROJECT_SOURCE_DIR}/src/parse.c)

install(TARGETS GahoodSON
        LIBRARY DESTINATION lib
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/GahoodSON" 
	DESTINATION include
)
