cmake_minimum_required(VERSION 3.29.3.0)
set(CMAKE_MODULE_PATH "C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6;C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6/3rdparty/kwin;C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6;C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;C:/Qt/6.7.3/mingw_64/lib/cmake/Qt6/3rdparty/kwin")
cmake_policy(SET CMP0128 OLD)
project(CMAKE_TRY_COMPILE CXX)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_LINKER_FLAGS}")
include_directories(${INCLUDE_DIRECTORIES})
set(CMAKE_SUPPRESS_REGENERATION 1)
link_directories(${LINK_DIRECTORIES})
add_definitions([==[-DHAVE_STDATOMIC]==])
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0083 NEW)
cmake_policy(SET CMP0155 OLD)
cmake_policy(SET CMP0157 OLD)
include("${CMAKE_ROOT}/Modules/Internal/HeaderpadWorkaround.cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/adbyb/OneDrive/Documentos/GitHub/Death-and-reincarnation/Death-and-reincarnation/build/Desktop_Qt_6_7_3_MinGW_64_bit-MinSizeRel/CMakeFiles/CMakeScratch/TryCompile-e2pszo")
add_executable(cmTC_2498e)
target_sources(cmTC_2498e PRIVATE
  "C:/Users/adbyb/OneDrive/Documentos/GitHub/Death-and-reincarnation/Death-and-reincarnation/build/Desktop_Qt_6_7_3_MinGW_64_bit-MinSizeRel/CMakeFiles/CMakeScratch/TryCompile-e2pszo/src.cxx"
)
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/cmTC_2498e_loc"
     CONTENT $<TARGET_FILE:cmTC_2498e>)
set_property(TARGET cmTC_2498e PROPERTY "CXX_STANDARD" "17")
set_property(TARGET cmTC_2498e PROPERTY "CXX_STANDARD_REQUIRED" "ON")
target_link_libraries(cmTC_2498e ${LINK_LIBRARIES})
