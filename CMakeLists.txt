cmake_minimum_required (VERSION 3.2)
project ( show_task )

set(EXE_NAME "${PROJECT_NAME}-bin")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#------------- Options ------------
set(ACE_ILP_ROOT "~/Downloads/softwares/ACE-ilProlog-1.2.20/linux/" CACHE PATH "Path to ACE root (same as set to path)")
set(PROLOG_EXECUTION_COMMAND "prolog" CACHE STRING "Command that runs prolog interpreter on shell (aliases not allowed)" )
#----------------------------------
configure_file(
		${PROJECT_SOURCE_DIR}/include/externalDefinitions.h.in
		externalDefinitions.h
)

find_package( OpenCV REQUIRED )
#[[
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
]]

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR}
	${OpenCV_INCLUDE_DIR}
)


file(GLOB HEADER_FILES
		include/*.h include/*.hpp
		#storage/*.h storage/*.hpp
		)

file(GLOB SOURCES
		src/*.cpp src/*.c src/*.cc
		#storage/*.cpp storage/*.c storage/*.cc
		)

add_executable(${EXE_NAME} ${SOURCES} ${HEADER_FILES})

set_target_properties(
	${EXE_NAME}
	PROPERTIES
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)


target_link_libraries( 
	${EXE_NAME}
	${OpenCV_LIBS}
)
