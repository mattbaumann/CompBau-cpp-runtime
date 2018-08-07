set(GCC_COVERAGE_COMPILE_FLAGS "-fexceptions -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(spdlog spdlog-0.14.0/spdlog.h)