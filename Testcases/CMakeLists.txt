cmake_minimum_required(VERSION 3.9)
project(testcase-analyzer)

set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/testcase-analyzer.cc"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../Analyzer"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Analyzer/FFT"
)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} gts)

#
# classifier
#

project(testcase-classifier)

set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/testcase-classifier.cc"
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/../Classifier"
)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} gts)
