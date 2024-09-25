cmake_minimum_required(VERSION 3.8)
project(CustomAllocator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE CMAKE_BUILD_TYPE "Release")

# Add source directories
aux_source_directory(src SOURCE_FILES)
aux_source_directory(test TEST_SOURCE_FILES)

# Find necessary packages
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)
add_library(allocator ${SOURCE_FILES})

# Enable testing
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add your source files
add_executable(
  testing
  test/test.cpp
  src/allocator.cpp
)

target_link_libraries(
  testing
  gtest_main
)

include(GoogleTest)
add_test(AllTests testing)
# Define the benchmark executable and link with allocator, benchmark, and Threads

add_executable(small small.cpp)
add_executable(large large.cpp)
add_executable(random random.cpp)

target_link_libraries(small PRIVATE allocator  Threads::Threads)
target_link_libraries(large PRIVATE allocator  Threads::Threads)
target_link_libraries(random PRIVATE allocator  Threads::Threads)


# Add test to CTest

