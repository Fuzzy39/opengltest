cmake_minimum_required(VERSION 3.28)

project(openGLTest LANGUAGES CXX C)


add_executable(gltest "src/gl.c" "src/main.cpp" "src/Disk.cpp" "src/setup.cpp" 
    "src/resources/Shader.cpp" "src/resources/Model.cpp" "src/resources/ResourceManager.cpp"
    "src/world/RenderObject.cpp" "src/world/World.cpp"
)
target_include_directories(gltest PUBLIC "include")

add_custom_command(
        TARGET gltest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders)

add_custom_command(
        TARGET gltest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources
                ${CMAKE_CURRENT_BINARY_DIR}/resources)

#add_executable(test0 "src/test0.cpp" )
#target_include_directories(gltest PUBLIC "include")

if (MSVC)
    # do something
    target_link_libraries(gltest ${CMAKE_SOURCE_DIR}/libglfw3/glfw3.lib)
    #target_link_libraries(test0 ${CMAKE_SOURCE_DIR}/libglfw3/glfw3.lib)
else()
    target_link_libraries(gltest ${CMAKE_SOURCE_DIR}/libglfw3/libglfw3.a)
    #target_link_libraries(test0 ${CMAKE_SOURCE_DIR}/libglfw3/libglfw3.a)
endif (MSVC)

