# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles\\Death-and-reincarnation_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Death-and-reincarnation_autogen.dir\\ParseCache.txt"
  "Death-and-reincarnation_autogen"
  )
endif()
