# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/nBodyGravitation_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/nBodyGravitation_autogen.dir/ParseCache.txt"
  "nBodyGravitation_autogen"
  )
endif()
