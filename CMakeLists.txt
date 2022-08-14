cmake_minimum_required(VERSION 3.10)

project(SignalTracer)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif()

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set(TRACER_SRC 
  src/actions.cpp
  src/attenuation.cpp
  src/configuration.cpp
  src/cutting_plane.cpp
  src/heatmap.cpp
  src/importer.cpp
  src/main.cpp
  src/marker.cpp
  src/matrix.cpp
  src/mesh.cpp
  src/model.cpp
  src/quaternion.cpp
  src/raycast.cpp
  src/renderer.cpp
  src/shaders.cpp
  src/vector.cpp
  src/window.cpp
)

add_executable(sigtracer ${TRACER_SRC})
set_property(TARGET sigtracer PROPERTY CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/package/")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(nlohmann_json REQUIRED)

add_dependencies(sigtracer OpenGL::OpenGL)

set(TRACER_LIBS atomic SDL2 GLEW OpenGL::OpenGL ${GLUT_LIBRARY} assimp nlohmann_json::nlohmann_json)

target_link_libraries(sigtracer PUBLIC m)
target_link_libraries(sigtracer PUBLIC ${TRACER_LIBS})
include_directories(sigtracer ./include ${SDL2_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} assimp nlohmann_json)

link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

add_custom_target(glsl-vertex ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/*.glsl)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/*.glsl
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/glsl/vertex.glsl
                                                    ${CMAKE_CURRENT_BINARY_DIR}/vertex.glsl
                   DEPENDS ./glsl/vertex.glsl)

add_custom_target(glsl-fragment ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/fragment.glsl)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fragment.glsl
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/glsl/fragment.glsl
                                                    ${CMAKE_CURRENT_BINARY_DIR}/fragment.glsl
                   DEPENDS ${PROJECT_SOURCE_DIR}/glsl/fragment.glsl)

add_custom_target(test-plan ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/plan.fbx ${CMAKE_CURRENT_BINARY_DIR}/plan-params.json)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/plan.fbx
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/test/plan.fbx
                                                    ${CMAKE_CURRENT_BINARY_DIR}/plan.fbx
                   DEPENDS ${PROJECT_SOURCE_DIR}/test/plan.fbx)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/plan-params.json
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/test/plan-params.json
                                                    ${CMAKE_CURRENT_BINARY_DIR}/plan-params.json
                   DEPENDS ${PROJECT_SOURCE_DIR}/test/plan-params.json)
                   