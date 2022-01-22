cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(scene VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(glm REQUIRED)
message(STATUS "glm included at ${glm_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")

find_package(glfw3 REQUIRED)
message(STATUS "Found glfw3 in ${glfw3_INCLUDE_DIR}")

set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${glm_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})

set(LOCAL_INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMAKE_SOURCE_DIR}/src/core"
    "${CMAKE_SOURCE_DIR}/src/lights"
    "${CMAKE_SOURCE_DIR}/src/renderer"
    "${CMAKE_SOURCE_DIR}/src/third_party")

set(LIBRARIES ${OPENGL_LIBRARIES} ${glm_LIBRARIES} ${GLEW_LIBRARIES} ${glfw3_LIBRARIES})

include_directories(${INCLUDE_DIRS} ${LOCAL_INCLUDE_DIRS})

set(SOURCE_FILES 
    main.cpp
    src/core/camera.cpp
    src/core/gl_window.cpp
    src/lights/directional_light.cpp
    src/lights/point_light.cpp
    src/lights/spot_light.cpp
    src/lights/light.cpp
    src/renderer/material.cpp
    src/renderer/mesh.cpp
    src/renderer/shader.cpp
    src/renderer/texture.cpp)


add_executable(scene ${SOURCE_FILES} )

target_link_libraries(scene ${LIBRARIES} glfw)

target_include_directories(scene PRIVATE ${LOCAL_INCLUDE_DIRS})