cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(myproject CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET myproject_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

add_executable(tests tests.cpp)
target_link_libraries(
  tests
  PRIVATE myproject::myproject_warnings
          myproject::myproject_options
          myproject::sample_library
          GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests XML_OUTPUT_DIR ${CMAKE_BINARY_DIR})
