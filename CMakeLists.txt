cmake_minimum_required(VERSION 3.10)

set(PROJECT_N ZhvRender)
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 OLD)
endif()

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/libs)

aux_source_directory(${PROJECT_SOURCE_DIR}/include/imgui IMGUI_SRC_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_FILES)

add_executable(ZhvRender ${IMGUI_SRC_FILES} ${SRC_FILES})

target_link_libraries(ZhvRender GL glfw)