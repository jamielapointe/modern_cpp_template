cmake_minimum_required(VERSION 3.25)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(myproject CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET myproject_options)
    message(FATAL_ERROR "Required config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

add_executable(
  myproject_tests
  test_binary_exponentiation.cpp
  test_breadth_first_search_unordered.cpp
  test_factorial.cpp
  test_fibonacci.cpp
  test_main.cpp)
target_include_directories(myproject_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${MYPROJECT_ROOT}/include
                                                   ${MYPROJECT_BUILD_ROOT}/configured_files/include)
target_link_libraries(myproject_tests PRIVATE myproject::myproject_options myproject::myproject_warnings)
target_link_system_libraries(
  myproject_tests
  PRIVATE
  GTest::gtest_main
  fmt::fmt
  spdlog::spdlog
  Microsoft.GSL::GSL)

include(GoogleTest)
gtest_discover_tests(myproject_tests XML_OUTPUT_DIR ${CMAKE_BINARY_DIR})
