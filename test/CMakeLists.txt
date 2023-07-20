cmake_minimum_required(VERSION 3.25)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(modern_cpp_template CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET modern_cpp_template_options)
    message(FATAL_ERROR "Required config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

add_executable(
  modern_cpp_template_tests
  test_binary_exponentiation.cpp
  test_breadth_first_search_unordered.cpp
  test_factorial.cpp
  test_fibonacci.cpp
  test_main.cpp)
target_include_directories(
  modern_cpp_template_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${modern_cpp_template_ROOT}/include
                                    ${modern_cpp_template_BUILD_ROOT}/configured_files/include)
target_link_libraries(modern_cpp_template_tests PRIVATE modern_cpp_template::modern_cpp_template_options
                                                        modern_cpp_template::modern_cpp_template_warnings)
target_link_system_libraries(
  modern_cpp_template_tests
  PRIVATE
  GTest::gtest_main
  fmt::fmt
  spdlog::spdlog
  Microsoft.GSL::GSL)

include(GoogleTest)
gtest_discover_tests(modern_cpp_template_tests XML_OUTPUT_DIR ${CMAKE_BINARY_DIR})
