cmake_minimum_required(VERSION 3.28)

project(openGLTest LANGUAGES CXX C)


add_executable(gltest "src/test.cpp")
target_include_directories(gltest PUBLIC "include")

if (MSVC)
    # do something
    target_link_libraries(gltest ${CMAKE_SOURCE_DIR}/libglfw3/glfw3.lib)
else()
    target_link_libraries(gltest ${CMAKE_SOURCE_DIR}/libglfw3/libglfw3.a)
endif (MSVC)

