cmake_minimum_required(VERSION 3.21)

project(OpenGLBasics C CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

file(GLOB SOURCES CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/include/*.h
        ${PROJECT_SOURCE_DIR}/src/src/*.cpp
        ${PROJECT_SOURCE_DIR}/lib/stb_image/stb_image.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
#        ${PROJECT_SOURCE_DIR}/src/test.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/lib/stb_image
        src/include
)

# copy res file
# https://stackoverflow.com/a/36533708/11718077
# https://stackoverflow.com/a/28548494/11718077
add_custom_target(copy_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/res" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy Resources directory to build tree"
        VERBATIM
)

add_executable(OpenGLBasics ${SOURCES} )
add_dependencies( OpenGLBasics copy_res_directory )

target_link_libraries(OpenGLBasics glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glad)
