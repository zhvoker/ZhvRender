cmake_minimum_required(VERSION 3.10)

set(PROJECT_N ZhvRender)
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 OLD)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/libs)

aux_source_directory(${PROJECT_SOURCE_DIR}/include/imgui IMGUI_SRC_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/include/stb_image STB_SRC_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_FILES)

add_executable(ZhvRender ${IMGUI_SRC_FILES} ${SRC_FILES} ${STB_SRC_FILES})

target_link_libraries(ZhvRender GL glfw glm::glm GLU)