cmake_minimum_required(VERSION 3.24.0-rc5 FATAL_ERROR)

set (PROJECT_NAME ProjectOne)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(externellib/glfw)
target_link_libraries (${PROJECT_NAME} glfw)

add_subdirectory(externellib/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)