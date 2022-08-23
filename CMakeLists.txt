cmake_minimum_required(VERSION 3.21)

project(OpenGLBasics C CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

list(APPEND SOURCES
    main.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(OpenGLBasics ${SOURCES} )

target_link_libraries(OpenGLBasics glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glad)
