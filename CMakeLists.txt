cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_EXTENSIONS OFF)

project(equivalentcircuitmodeler)

add_executable(${PROJECT_NAME} 
	src/interface.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>
)

add_subdirectory(src)
add_subdirectory(lib)

file(MAKE_DIRECTORY data)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	circuit
)
