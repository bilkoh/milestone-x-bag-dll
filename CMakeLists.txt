cmake_minimum_required(VERSION 3.5.0)
project(bag VERSION 0.1.0 LANGUAGES C CXX)

# Set up the warnings I like
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
endif()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GTest Block Start
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()
add_executable(bag_test bag_test.cc bag.cpp dll_node.cpp doubly_linked_list.cpp)
target_link_libraries(bag_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(bag_test)
# GTest Block End

# main executable
add_executable(bag main.cpp bag.cpp dll_node.cpp doubly_linked_list.cpp)

# Add a custom target to run tests automatically after the build
add_custom_target(
  run_all_tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
  DEPENDS bag_test
)

# Make the custom target run after the build
add_dependencies(bag run_all_tests)