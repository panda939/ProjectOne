cmake_minimum_required(VERSION 3.24.0-rc5 FATAL_ERROR)
project(Glad)

add_library (glad STATIC include/glad/glad.h src/glad.c)

target_link_directories(glad PUBLIC include/)
