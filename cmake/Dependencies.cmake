include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET fmtlib::fmtlib)
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.11.0
      GITHUB_REPOSITORY
      "gabime/spdlog"
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON")
  endif()

  if(NOT TARGET CLI11::CLI11)
    cpmaddpackage("gh:CLIUtils/CLI11@2.3.2")
  endif()

  if(NOT TARGET tools::tools)
    cpmaddpackage("gh:lefticus/tools#update_build_system")
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
      "BENCHMARK_ENABLE_TESTING Off"
      "CMAKE_BUILD_TYPE Release")

    # add customizable options to include LIBPFM and LTO

    if(benchmark_ADDED)
      # enable c++11 to avoid compilation errors
      set_target_properties(benchmark PROPERTIES CXX_STANDARD 11)
    endif()
  endif()

  if(NOT TARGET googletest::googletest)
    cpmaddpackage(
      NAME
      googletest
      GITHUB_REPOSITORY
      google/googletest
      GIT_TAG
      v1.13.0
      VERSION
      1.13.0
      OPTIONS
      "INSTALL_GTEST OFF"
      "gtest_force_shared_crt ON"
      "CMAKE_BUILD_TYPE Release"
      "CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF")
  endif()

endfunction()
