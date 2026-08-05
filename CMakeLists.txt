cmake_minimum_required(VERSION 3.27)
project(shooter)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)

add_executable(shooter
        main.cpp
        glad.c
        include/Shader.h
        src/Shader.cpp
        libraries/stb/stb_image.h
        src/stb.cpp
        include/Shader.h
        include/Sphere.h
        src/Sphere.cpp
)

target_include_directories(shooter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(shooter PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(shooter PRIVATE ${CMAKE_SOURCE_DIR}/libraries)


target_link_libraries(shooter PRIVATE glfw "-framework OpenGL")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
