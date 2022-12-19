add_library(circuit circuit.cpp)
target_include_directories(circuit PUBLIC .)

set_target_properties(circuit PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
)