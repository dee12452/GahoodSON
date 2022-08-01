cmake_minimum_required(VERSION 2.6.8)
project(GahoodSON)

include_directories(./include/)
add_library(GahoodSON STATIC ./src/parse.c)
