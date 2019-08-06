cmake_minimum_required (version 2.6)
project (miniprojects main.cc)

set (Sound_CONFIG_VERSION 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/SoundData.h.in"
  "${PROJECT_BINARY_DIR}/SoundData.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/FourierTransform")

add_subdirectory (FourierTransform)

add_executable (miniprojects main.cc)
target_link_libraries (miniprojects FourierTransform)
