cmake_minimum_required(VERSION 2.8.2)

project(boost_multi_index_benchmark C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

###########################################################

add_subdirectory(deps/google_benchmark EXCLUDE_FROM_ALL)

###########################################################

# Checking boost ...
find_package(Boost 1.58.0 REQUIRED COMPONENTS system)

# Checking compiler for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(NOT COMPILER_SUPPORTS_CXX11)
  message(FATAL_ERROR
          "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS src/main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS
                            "-Wuninitialized -Wpedantic -Wextra -Wall")

include_directories(SYSTEM PRIVATE ${Boost_INCLUDE_DIRS} deps/google_benchmark/include)
target_link_libraries(${CMAKE_PROJECT_NAME} benchmark ${Boost_LIBRARIES})
