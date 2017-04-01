# zedengine library cmakelists.txt

project(zedengine)

# add sources to library
set(ZEDENGINE_SOURCES ${PROJECT_SOURCE_DIR}/src/glsl_program.cpp
  ${PROJECT_SOURCE_DIR}/src/image_loader.cpp
  ${PROJECT_SOURCE_DIR}/src/io_manager.cpp
  ${PROJECT_SOURCE_DIR}/src/pico_png.cpp
  ${PROJECT_SOURCE_DIR}/src/resource_manager.cpp
  ${PROJECT_SOURCE_DIR}/src/sprite.cpp
  ${PROJECT_SOURCE_DIR}/src/texture_cache.cpp)

# set include directory
include_directories(${ZEDENGINE_INCLUDE_DIRS})

# make it a static library
add_library(${PROJECT_NAME} ${ZEDENGINE_SOURCES})
