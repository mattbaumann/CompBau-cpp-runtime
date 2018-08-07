cmake_minimum_required(VERSION 3.7)

include(cmake/doxygen.cmake)

# ==============================================================================
# Project config
# ==============================================================================

project(CompBau_cpp_runtime VERSION 0.0.1 LANGUAGES "CXX")

set(CMAKE_BUILD_TYPE Release CACHE STRING "Project build type" FORCE)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# The source container names
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# CPP standard version
set(CMAKE_CXX_STANDARD 17)

# Compiler options
set(GCC_COVERAGE_COMPILE_FLAGS "-fexceptions -fpermissive -fprofile-arcs -ftest-coverage -fPIC")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov -lpthread -lboost_system -lboost_thread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Set the CPP files which should be compiled
set(SOURCE_FILES
        src/HelloWorld.cpp
        )

add_library(SRC ${SOURCE_FILES})

# ==============================================================================
# Boost config
# ==============================================================================
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.62 REQUIRED)

target_include_directories(SRC PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(SRC PUBLIC ${Boost_LIBRARIES})

# ==============================================================================
# Doxygen Support
# ==============================================================================

build_doxygen()

# ==============================================================================
# Testing Support
# ==============================================================================
enable_testing()

include_directories(${TEST_DIR} ${SOURCE_DIR} ${LIB_DIR})

set(TEST_FILES
        test/main.cpp
        test/HelloWorldTest.cpp
        )

add_executable(unit-test ${LIB_DIR}/catch-1.10.h ${TEST_FILES})

target_link_libraries(unit-test PUBLIC SRC)
set_target_properties(unit-test PROPERTIES LINKER_LANGUAGE CXX)

add_test(NAME ctest_compbau_tests CONFIGURATIONS Debug COMMAND unit-test)
