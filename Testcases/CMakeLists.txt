cmake_minimum_required(VERSION 3.9)
project(testcase-analyzer)

set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/testcase-analyzer.cc"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Analyzer")

set(COMMON_WARNINGS					"-Wall")
set(CMAKE_CXX_FLAGS_DEBUG           "-g ${COMMON_WARNINGS}")
set(CMAKE_CXX_FLAGS_RELEASE         "-O2 ${COMMON_WARNINGS}")
set(CMAKE_CXX_FLAGS_PROFILE         "-O2 -pg ${COMMON_WARNINGS}")

add_executable(${PROJECT_NAME} ${SRCS})
