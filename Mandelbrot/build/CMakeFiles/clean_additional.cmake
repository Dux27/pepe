# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/Mandelbrot_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Mandelbrot_autogen.dir/ParseCache.txt"
  "Mandelbrot_autogen"
  )
endif()
