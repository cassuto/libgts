cmake_minimum_required(VERSION 3.9)
project(libgts)
set(TARGET_LIB "gts")

add_subdirectory(Testcases)

set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/Analyzer/AnalysisChroma.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/Analyzer/IIR-Filter.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/Analyzer/FFT/kiss_fft.c"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Analyzer")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Classifier")

set(COMMON_WARNINGS					"-Wall")

set(CMAKE_CXX_FLAGS_DEBUG           "-g ${COMMON_WARNINGS}")
set(CMAKE_CXX_FLAGS_RELEASE         "-O2 ${COMMON_WARNINGS}")
set(CMAKE_CXX_FLAGS_PROFILE         "-O2 -pg ${COMMON_WARNINGS}")

set(CMAKE_MODULE_LINKER_FLAGS_PROFILE "-pg")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "-pg")

add_library(${TARGET_LIB} ${SRCS})
