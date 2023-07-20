include(CPM)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(modern_cpp_template_setup_dependencies)

  # This sets this variable for this scope only
  set(CMAKE_BUILD_TYPE Release)

  if(NOT TARGET fmt::fmt)
    cpmaddpackage(
      NAME
      fmt
      GIT_TAG
      10.0.0
      VERSION
      10.0.0
      GITHUB_REPOSITORY
      fmtlib/fmt
      OPTIONS
      "FMT_INSTALL OFF"
      "FMT_TEST OFF"
      "FMT_SYSTEM_HEADERS ON"
      "FMT_DEBUG_POSTFIX ")
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.12.0
      GITHUB_REPOSITORY
      gabime/spdlog
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON"
      "SPDLOG_BUILD_EXAMPLE OFF"
      "SPDLOG_INSTALL OFF"
      "SPDLOG_SYSTEM_INCLUDES ON")
  endif()
  if(spdlog_ADDED)
    set_property(TARGET spdlog PROPERTY DEBUG_POSTFIX)
  endif()

  if(NOT TARGET CLI11::CLI11)
    cpmaddpackage(
      NAME
      CLI11
      GITHUB_REPOSITORY
      CLIUtils/CLI11
      VERSION
      2.3.2
      OPTIONS
      "CLI11_BUILD_DOCS OFF"
      "CLI11_BUILD_EXAMPLES OFF"
      "CLI11_BUILD_TESTS OFF"
      "CLI11_INSTALL OFF")
  endif()

  if(NOT TARGET benchmark::benchmark)
    cpmaddpackage(
      NAME
      benchmark
      GITHUB_REPOSITORY
      google/benchmark
      VERSION
      1.8.0
      OPTIONS
      "BENCHMARK_ENABLE_TESTING OFF"
      "BENCHMARK_ENABLE_LIBPFM ${modern_cpp_template_ENABLE_LIBPFM}")

    if(CMAKE_BUILD_TYPE STREQUAL "Release" AND modern_cpp_template_ENABLE_SIMD)
      set_target_properties(benchmark PROPERTIES COMPILE_FLAGS -ffast-math)
      if(modern_cpp_template_ENABLE_NATIVE_ARCHITECTURE)
        set_target_properties(benchmark PROPERTIES COMPILE_FLAGS -march=native)
      endif()
    endif()
  endif()

  if(NOT TARGET googletest::googletest)
    cpmaddpackage(
      NAME
      googletest
      GITHUB_REPOSITORY
      google/googletest
      VERSION
      1.13.0
      OPTIONS
      "INSTALL_GTEST OFF"
      "gtest_force_shared_crt ON"
      "CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF")
  endif()
  if(googletest_ADDED)
    # disable annoying compiler warnings in GoogleTest
    if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set_target_properties(gtest PROPERTIES COMPILE_FLAGS -Wno-implicit-int-float-conversion)
      set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS -Wno-implicit-int-float-conversion)
    endif()
  endif()

  if(NOT TARGET Microsoft.GSL::GSL)
    cpmaddpackage(
      NAME
      GSL
      GITHUB_REPOSITORY
      microsoft/GSL
      VERSION
      4.0.0
      OPTIONS
      "GSL_CXX_STANDARD ${CMAKE_CXX_STANDARD}"
      "GSL_INSTALL OFF"
      "GSL_TEST OFF")
  endif()

  if(NOT TARGET abseil::base)
    cpmaddpackage(
      NAME
      abseil
      GITHUB_REPOSITORY
      abseil/abseil-cpp
      GIT_TAG
      20230125.3
      VERSION
      20230125.3
      OPTIONS
      "ABSL_BUILD_TESTING OFF"
      "ABSL_ENABLE_INSTALL OFF"
      "ABSL_USE_SYSTEM_INCLUDES ON"
      "ABSL_PROPAGATE_CXX_STD ON"
      "BUILD_TESTING OFF"
      "CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD}")
  endif()
endfunction()
