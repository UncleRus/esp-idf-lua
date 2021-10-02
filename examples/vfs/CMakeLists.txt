cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(example-lua-vfs)

spiffs_create_partition_image(storage spiffs_image FLASH_IN_PROJECT)
