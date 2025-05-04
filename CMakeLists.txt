cmake_minimum_required(VERSION 3.10.0)
project(W2DR VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_subdirectory("${CMAKE_SOURCE_DIR}\\ExternalDependencies\\GLFW")
add_subdirectory("${CMAKE_SOURCE_DIR}\\ExternalDependencies\\GLAD")

file(GLOB_RECURSE MY_SOURCES CONFIG_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(W2DR "${MY_SOURCES}")
target_include_directories(W2DR PRIVATE "${CMAKE_SOURCE_DIR}/include/")

target_link_libraries(W2DR glfw)
target_link_libraries(W2DR glad)