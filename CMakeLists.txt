cmake_minimum_required(VERSION 3.21)

project(OpenGLBasics C CXX)
set(CMAKE_CXX_STANDARD 20)

set( GRAPHICS_RES_DIR "${CMAKE_SOURCE_DIR}/res" )
set( GRAPHICS_TEST_RES_DIR "${CMAKE_SOURCE_DIR}/tests/res" )

# copy res file
# https://stackoverflow.com/a/36533708/11718077
# https://stackoverflow.com/a/28548494/11718077
add_custom_target(copy_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GRAPHICS_RES_DIR}" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy Resources directory to build tree"
        VERBATIM
        )
add_custom_target(copy_test_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GRAPHICS_TEST_RES_DIR}" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy Resources directory to build tree"
        VERBATIM
        )

add_subdirectory(lib/imgui)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/spdlog)

file(GLOB SOURCES CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/core/include/*.h
        ${PROJECT_SOURCE_DIR}/core/src/*.cpp
        ${PROJECT_SOURCE_DIR}/graphics/opengl/include/*.h
        ${PROJECT_SOURCE_DIR}/graphics/opengl/src/*.cpp
        ${PROJECT_SOURCE_DIR}/lib/stb_image/*.cpp
        ${PROJECT_SOURCE_DIR}/lib/stb_image/*.h
        ${PROJECT_SOURCE_DIR}/tests/src/*.cpp
        ${PROJECT_SOURCE_DIR}/tests/*.h
        main.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/lib/stb_image
        ${PROJECT_SOURCE_DIR}/lib/glm
        ${PROJECT_SOURCE_DIR}/lib/spdlog/include
        core/include
        graphics/opengl/include
)

add_executable(OpenGLBasics ${SOURCES} )

add_dependencies( OpenGLBasics copy_res_directory )
add_dependencies( OpenGLBasics copy_test_res_directory )

target_link_libraries(
        OpenGLBasics
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        glad
        imgui
        spdlog
)
