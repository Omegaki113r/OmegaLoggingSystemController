# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set( LOGGING_CONTROLLER_PATH ../.. )

set( EXTRA_COMPONENT_DIRS ${LOGGING_CONTROLLER_PATH} )


if (WIN32)
  set(CMAKE_OBJECT_PATH_MAX 264)
endif ()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(Logging)

spiffs_create_partition_image(storage storage FLASH_IN_PROJECT)