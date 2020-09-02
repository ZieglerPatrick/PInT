file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_llvm_executable (HPC-pattern-tool ${SOURCES})

target_compile_options(HPC-pattern-tool
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fexceptions >
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti >
)

target_link_libraries (HPC-pattern-tool PUBLIC ${llvm_libs} clangBasic clangTooling)
