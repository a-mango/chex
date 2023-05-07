cmake_minimum_required(VERSION 3.25)
project(chex)

# Set the C standard to C23
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)

# Set default compile flags for GCC
set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")
add_compile_options(-Wformat -Wshadow -Wpointer-arith -Wcast-align -Wstrict-overflow -Wparentheses -Wunreachable-code -Winline -Wswitch-enum -Wlogical-op -Wnull-dereference -Wformat-nonliteral -Wvla -Wdouble-promotion)

# Set conditional compile flags
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
    add_compile_options(-g3 -fPIE -pie)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
    add_compile_options(-Ofast -Werror)
endif ()

# Add the GTest library
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Enable sanitizers
# Requires: libasan, libubsan, liblsan, libtsan
# Windows users: try to install the LLVM toolchain or use WSL
option(ENABLE_ASAN "Enable asan" OFF)
if (ENABLE_ASAN AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND CMAKE_BUILD_TYPE MATCHES Debug)
    # Check if the required sanitizing libraries are present
    set(SAN_OPT "-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,alignment,signed-integer-overflow,shift,integer-divide-by-zero,null")
    message(STATUS "Enabling sanitizers")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SAN_OPT} -fstack-protector")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SAN_OPT}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SAN_OPT}")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SAN_OPT}")
endif ()

# Include additional libraries or header files (if any)
# include_directories(include)
# add_library(mylib src/mylib.c)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# Add the executable(s)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Add test files
file(GLOB_RECURSE TEST_FILES
	${CMAKE_SOURCE_DIR}/test/*.cpp)

# Configure Google Test
enable_testing()
add_executable(chex_test ${TEST_FILES} src/board.c src/util.c src/print.c)
target_link_libraries(chex_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(chex_test)
