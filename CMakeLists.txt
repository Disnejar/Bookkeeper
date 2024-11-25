cmake_minimum_required(VERSION 3.5.0)
project(Bookkeeper VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

# GLFW
set(GLFW_DIR glfw) # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)
#include_directories(${GLFW_DIR}/deps)

# stb
set(STB_DIR ${PROJECT_SOURCE_DIR}/stb)
add_library(stb STATIC ${STB_DIR})
set_target_properties(stb PROPERTIES LINKER_LANGUAGE C)
include_directories(${STB_DIR})

# Dear ImGui
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/imgui)
file(GLOB IMGUI_SRC CONFIGURE_DEPENDS ${IMGUI_DIR}/*.cpp)
set(IMGUI_SRC ${IMGUI_SRC} ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp)
add_library(imgui STATIC ${IMGUI_SRC})
set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${IMGUI_DIR})
target_link_libraries(imgui "glfw;Vulkan::Vulkan;stb")

# ImFileDialog
set(IMFILEDIALOG_DIR ${PROJECT_SOURCE_DIR}/ImFileDialog)
file(GLOB IMFILEDIALOG_SRC CONFIGURE_DEPENDS ${IMFILEDIALOG_DIR}/ImFileDialog.cpp)
include_directories(${IMFILEDIALOG_DIR})

# ImDatePicker
set(IMDATEPICKER_DIR ${PROJECT_SOURCE_DIR}/ImGuiDatePicker)
file(GLOB IMDATEPICKER_SRC CONFIGURE_DEPENDS ${IMDATEPICKER_DIR}/ImGuiDatePicker.cpp)
include_directories(${IMDATEPICKER_DIR})

add_library(imgui_addons STATIC ${IMFILEDIALOG_SRC} ${IMDATEPICKER_SRC})
set_target_properties(imgui_addons PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(imgui_addons "imgui;stb")

find_package(Vulkan REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan;imgui;stb;imgui_addons")

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DImTextureID=ImU64)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        # If the debug configuration pass the DEBUG define to the compiler 
        $<$<CONFIG:Debug>:DEBUG_MODE>
)
