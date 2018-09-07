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
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Set the CPP files which should be compiled
set(SOURCE_FILES
        src/runner.cpp
        src/Runtime.cpp
        src/parser/parser.cpp
        src/linker/linker.cpp
        src/il/method.cpp
        )

add_library(SRC ${SOURCE_FILES})

# ==============================================================================
# Boost config
# ==============================================================================
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.62 REQUIRED)

target_include_directories(SRC PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(SRC PUBLIC ${Boost_LIBRARIES})

# ==============================================================================
# YAML-CPP config
# ==============================================================================

find_package(yaml-cpp REQUIRED)

target_include_directories(SRC PUBLIC yaml-cpp)
target_link_libraries(SRC PUBLIC yaml-cpp)

# ==============================================================================
# spdlog config
# ==============================================================================

find_package(spdlog REQUIRED)

target_include_directories(SRC PUBLIC spdlog)
target_link_libraries(SRC PUBLIC pthread)

# ==============================================================================
# Doxygen Support
# ==============================================================================

build_doxygen()

# ==============================================================================
# Executable
# ==============================================================================

add_executable(cpp-runtime main.cpp)

target_link_libraries(cpp-runtime PUBLIC SRC)
set_target_properties(cpp-runtime PROPERTIES LINKER_LANGUAGE CXX)

# ==============================================================================
# Testing Support
# ==============================================================================
enable_testing()

include_directories(${TEST_DIR} ${SOURCE_DIR} ${LIB_DIR})

set(TEST_FILES
        test/main.cpp
        test/parser/parser_test.cpp
        test/linker/linker_test.cpp
        test/utils_test.cpp
        test/il/array_type_test.cpp
        test/il/build_in_type_test.cpp
        test/il/class_type_test.cpp
        test/il/method_test.cpp)

add_executable(unit-test ${LIB_DIR}/catch.hpp ${TEST_FILES})

target_link_libraries(unit-test PUBLIC SRC)
set_target_properties(unit-test PROPERTIES LINKER_LANGUAGE CXX)

add_test(NAME ctest_compbau_tests CONFIGURATIONS Debug COMMAND unit-test)
