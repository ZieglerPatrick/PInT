cmake_minimum_required (VERSION 3.12)
project (HPC-pattern-tool)

cmake_policy(SET CMP0074 NEW)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wall -Wextra")
set (CMAKE_BUILD_TYPE Debug)

set (SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)
set (HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)

########################################################################
#                                                                      #
#  Import Clang + Dependencies                                         #
#                                                                      #
########################################################################
set (CLANG_INCLUDE_DIR "/usr/lib/clang/12" CACHE STRING
	"Directory where the clang system library header files are located")
add_definitions (-DCLANG_INCLUDE_DIR="${CLANG_INCLUDE_DIR}")

set (PRINT_DEBUG_INFORMATION OFF CACHE BOOL
	"Toogle output of AST Information and RAW Comment List")
if (PRINT_DEBUG_INFORMATION)
	add_definitions (-DPRINT_DEBUG)
endif ()


find_package(Clang REQUIRED clangTooling libClang clangAST)
message (STATUS "Found clang ${CLANG_VERSION_STRING}")

find_package(LLVM REQUIRED CONFIG)
message (STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message (STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

set(LLVM_ENABLE_EH ON)
message(STATUS "LLVM_ENABLE_EH: ${LLVM_ENABLE_EH}")

include_directories(SYSTEM ${CLANG_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS} ${CLANG_DEFINITIONS})

########################################################################
#                                                                      #
#  Build project                                                       #
#                                                                      #
########################################################################

include_directories(${HEADERS_DIR})
add_subdirectory(${SOURCES_DIR})
