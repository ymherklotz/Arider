cmake_minimum_required(VERSION 3.0)
project(arider)

# set version number
set(ARIDER_MAJOR_VERSION 0)
set(ARIDER_MINOR_VERSION 1)
set(ARIDER_PATCH_VERSION 0)
set(ARIDER_VERSION
  ${ARIDER_MAJOR_VERSION}.${ARIDERn_MINOR_VERSION}.${ARIDER_PATCH_VERSION})

# set standard
set(CMAKE_CXX_STANDARD 14)

# set include directories
set(ARIDER_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)

# setting right output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


set(YAGE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/yage/include/)
set(YAGE_LIBRARIES yage)

# setting up configuration header
configure_file (
  ${CMAKE_SOURCE_DIR}/config/arider_config.hpp.in
  ${CMAKE_SOURCE_DIR}/include/arider_config.hpp
  )

# adding my executable
add_executable(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/src/game.cpp
  ${CMAKE_SOURCE_DIR}/src/main.cpp)

# adding sdl2 library
include(FindPkgConfig)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

# add zedengine library
add_subdirectory(yage)

# adding include directories
include_directories(${ARIDER_INCLUDE_DIRS}
  ${YAGE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${SLD2_INCLUDE_DIRS})

# link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${YAGE_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES})
