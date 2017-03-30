cmake_minimum_required(VERSION 2.8)
project(arider)

# set version number
set(ARIDER_MAJOR_VERSION 0)
set(ARIDER_MINOR_VERSION 1)
set(ARIDER_PATCH_VERSION 0)
set(ARIDER_VERSION
  ${ARIDER_MAJOR_VERSION}.${ARIDER_MINOR_VERSION}.${ARIDER_PATCH_VERSION})

# set standard
set(CMAKE_CXX_STANDARD 14)

# set include directories
set(ARIDER_INCLUDE_DIR "include/")

# setting right output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

# setting up configuration header
configure_file (
  "config/arider_config.hpp.in"
  "include/arider_config.hpp"
  )

# adding my executable
add_executable(${PROJECT_NAME} "src/arider.cpp" "src/game.cpp" "src/sprite.cpp")

# adding sdl2 library
include(FindPkgConfig)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

# adding include directories
include_directories(${ARIDER_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS})

# link libraries
target_link_libraries(${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES})
