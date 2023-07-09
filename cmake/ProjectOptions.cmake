include(SystemLink)
include(LibFuzzer)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

# Test if compiler supports Sanitizers
# Parameters: <none>
macro(myproject_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

# Set up user configurable CMake options
# Parameters: <none>
macro(myproject_setup_options)
  if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(DEFAULT_HARDENING ON)
    set(DEFAULT_IPO ON)
    set(DEFAULT_PFM ON)
    set(DEFAULT_ASAN OFF)
    set(DEFAULT_UBSAN OFF)
  else()
    set(DEFAULT_HARDENING OFF)
    set(DEFAULT_IPO OFF)
    set(DEFAULT_PFM OFF)
    set(DEFAULT_ASAN ${SUPPORTS_ASAN})
    set(DEFAULT_UBSAN ${SUPPORTS_UBSAN})
  endif()

  option(myproject_ENABLE_HARDENING "Enable hardening" ${DEFAULT_HARDENING})
  option(myproject_ENABLE_COVERAGE "Enable coverage reporting" OFF)

  myproject_supports_sanitizers()

  find_package(Doxygen OPTIONAL_COMPONENTS dot)
  if(Doxygen_FOUND)
    set(DEFAULT_DOXYGEN ON)
  else()
    set(DEFAULT_DOXYGEN OFF)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    option(myproject_BUILD_DOCUMENTATION "Generate Doxygen documentation" OFF)
    option(myproject_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(myproject_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" OFF)
    option(myproject_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(myproject_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(myproject_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(myproject_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(myproject_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(myproject_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(myproject_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(myproject_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(myproject_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(myproject_ENABLE_PCH "Enable precompiled headers" OFF)
    option(myproject_ENABLE_CACHE "Enable ccache" OFF)
    option(myproject_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(myproject_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(myproject_ENABLE_INTERNAL_DEBUGGING "Enable internal debugging - this is for testintg this project only" OFF)
    option(myproject_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(
      myproject_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware arhcitecutres or cross compiling!"
      OFF)
  else()
    option(myproject_BUILD_DOCUMENTATION "Generate Doxygen documentation" ${DEFAULT_DOXYGEN})
    option(myproject_ENABLE_IPO "Enable IPO/LTO" ${DEFAULT_IPO})
    option(myproject_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" ${DEFAULT_PFM})
    option(myproject_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(myproject_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${DEFAULT_ASAN})
    option(myproject_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" ${DEFAULT_ASAN})
    option(myproject_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${DEFAULT_UBSAN})
    option(myproject_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(myproject_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(myproject_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(myproject_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(myproject_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(myproject_ENABLE_PCH "Enable precompiled headers" OFF)
    option(myproject_ENABLE_CACHE "Enable ccache" ON)
    option(myproject_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(myproject_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(myproject_ENABLE_INTERNAL_DEBUGGING "Enable internal debugging - this is for testintg this project only" ON)
    option(myproject_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(
      myproject_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware arhcitecutres or cross compiling!"
      OFF)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      myproject_ENABLE_IPO
      myproject_ENABLE_USER_LINKER
      myproject_ENABLE_SANITIZER_ADDRESS
      myproject_ENABLE_SANITIZER_LEAK
      myproject_ENABLE_SANITIZER_UNDEFINED
      myproject_ENABLE_SANITIZER_THREAD
      myproject_ENABLE_SANITIZER_MEMORY
      myproject_ENABLE_UNITY_BUILD
      myproject_ENABLE_CLANG_TIDY
      myproject_ENABLE_CPPCHECK
      myproject_ENABLE_COVERAGE
      myproject_ENABLE_PCH
      myproject_ENABLE_CACHE
      myproject_ENABLE_SAMPLE_BASED_PROFILING
      myproject_ENABLE_INSTRUMENTED_PROFILING
      myproject_ENABLE_SIMD
      myproject_ENABLE_NATIVE_ARCHITECTURE)
  endif()

  myproject_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (myproject_ENABLE_SANITIZER_ADDRESS OR myproject_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(myproject_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

# Setup the global options - effects myproject targets as well as third party
# dependencies
macro(myproject_global_options)
  if(myproject_ENABLE_IPO)
    include(InterproceduralOptimization)
    myproject_enable_ipo()
  endif()

  include(Profiling)
  if(myproject_ENABLE_SAMPLE_BASED_PROFILING)
    myproject_enable_sample_based_profiling()
  endif()
  if(myproject_ENABLE_INSTRUMENTED_PROFILING)
    myproject_enable_instrumented_profiling()
  endif()

  myproject_supports_sanitizers()
endmacro()

# Setup the local options - only affects myproject targets
macro(myproject_local_options)
  # setup the fake targets that store the common compiler settings
  add_library(myproject_warnings INTERFACE)
  add_library(myproject::myproject_warnings ALIAS myproject_warnings)

  add_library(myproject_options INTERFACE)
  add_library(myproject::myproject_options ALIAS myproject_options)
  target_compile_features(myproject_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

  if(PROJECT_IS_TOP_LEVEL)
    include(CompilerSettings)
  endif()

  include(CompilerWarnings)
  myproject_set_project_warnings(myproject_warnings)

  if(myproject_ENABLE_USER_LINKER)
    include(Linker)
    configure_linker(myproject_options)
  endif()

  include(Sanitizers)
  myproject_enable_sanitizers(
    myproject_options
    ${myproject_ENABLE_SANITIZER_ADDRESS}
    ${myproject_ENABLE_SANITIZER_LEAK}
    ${myproject_ENABLE_SANITIZER_UNDEFINED}
    ${myproject_ENABLE_SANITIZER_THREAD}
    ${myproject_ENABLE_SANITIZER_MEMORY})

  if(myproject_ENABLE_LIBPFM)
    find_package(PFM)
    if(HAVE_PFM)
      target_link_libraries(myproject_options PRIVATE pfm)
    endif()
  endif()

  set_target_properties(myproject_options PROPERTIES UNITY_BUILD ${myproject_ENABLE_UNITY_BUILD})

  if(myproject_ENABLE_PCH)
    target_precompile_headers(
      myproject_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(myproject_ENABLE_CACHE)
    include(CCache)
    myproject_enable_cache()
  endif()

  include(StaticAnalyzers)
  if(myproject_ENABLE_CLANG_TIDY)
    myproject_enable_clang_tidy(myproject_options)
  endif()

  if(myproject_ENABLE_CPPCHECK)
    # Use Default CPPCHECK settings
    # otherwise pass in string of your own settings
    myproject_enable_cppcheck("")
  endif()

  if(myproject_ENABLE_COVERAGE)
    myproject_enable_coverage(myproject_options)
  endif()

  if(myproject_BUILD_DOCUMENTATION)
    include(Doxygen)
    myproject_enable_doxygen("")
  endif()

  check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
  if(LINKER_FATAL_WARNINGS)
    # This is not working consistently, so disabling for now
    # target_link_options(myproject_options INTERFACE -Wl,--fatal-warnings)
  endif()

  if(myproject_ENABLE_HARDENING)
    include(Hardening)
    if(NOT SUPPORTS_UBSAN
       OR myproject_ENABLE_SANITIZER_UNDEFINED
       OR myproject_ENABLE_SANITIZER_ADDRESS
       OR myproject_ENABLE_SANITIZER_THREAD
       OR myproject_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    myproject_enable_hardening(myproject_options ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
