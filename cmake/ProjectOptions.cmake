include(SystemLink)
include(LibFuzzer)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

# Test if compiler supports Sanitizers
# Parameters: <none>
macro(modern_cpp_template_supports_sanitizers)
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
macro(modern_cpp_template_setup_options)
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

  option(modern_cpp_template_ENABLE_HARDENING "Enable hardening" ${DEFAULT_HARDENING})
  option(modern_cpp_template_ENABLE_COVERAGE "Enable coverage reporting" OFF)

  modern_cpp_template_supports_sanitizers()

  # adjust as needed; pretty sure we need 1.9.7 to get the MathJax3 and chtml support
  # not sure about an upper limit...
  find_package(Doxygen 1.9.7...<2.0 OPTIONAL_COMPONENTS dot)
  if(Doxygen_FOUND)
    set(DEFAULT_DOXYGEN ON)
  else()
    set(DEFAULT_DOXYGEN OFF)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    option(modern_cpp_template_BUILD_DOCUMENTATION "Generate Doxygen documentation" OFF)
    option(modern_cpp_template_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(modern_cpp_template_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" OFF)
    option(modern_cpp_template_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(modern_cpp_template_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(modern_cpp_template_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(modern_cpp_template_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(modern_cpp_template_ENABLE_PCH "Enable precompiled headers" OFF)
    option(modern_cpp_template_ENABLE_CACHE "Enable ccache" OFF)
    option(modern_cpp_template_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(modern_cpp_template_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(modern_cpp_template_ENABLE_INTERNAL_DEBUGGING
           "Enable internal debugging - this is for testintg this project only" OFF)
    option(modern_cpp_template_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(modern_cpp_template_ENABLE_DOXYGEN_WITH_CLANG "You have a version of doxygen that does supports clang" OFF)
    option(
      modern_cpp_template_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware architectures or cross compiling!"
      OFF)
  else()
    option(modern_cpp_template_BUILD_DOCUMENTATION "Generate Doxygen documentation" ${DEFAULT_DOXYGEN})
    option(modern_cpp_template_ENABLE_IPO "Enable IPO/LTO" ${DEFAULT_IPO})
    option(modern_cpp_template_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" ${DEFAULT_PFM})
    option(modern_cpp_template_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${DEFAULT_ASAN})
    option(modern_cpp_template_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" ${DEFAULT_ASAN})
    option(modern_cpp_template_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${DEFAULT_UBSAN})
    option(modern_cpp_template_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(modern_cpp_template_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(modern_cpp_template_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(modern_cpp_template_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(modern_cpp_template_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(modern_cpp_template_ENABLE_PCH "Enable precompiled headers" OFF)
    option(modern_cpp_template_ENABLE_CACHE "Enable ccache" ON)
    option(modern_cpp_template_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(modern_cpp_template_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(modern_cpp_template_ENABLE_INTERNAL_DEBUGGING
           "Enable internal debugging - this is for testintg this project only" ON)
    option(modern_cpp_template_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(
      modern_cpp_template_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware architectures or cross compiling!"
      OFF)
    option(
      modern_cpp_template_ENABLE_DOXYGEN_WITH_CLANG
      "Enable if you have a version of doxygen that was linked with the clang 16.0+ library; this is useful for getting better parsing of C++ code"
      OFF)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      modern_cpp_template_ENABLE_IPO
      modern_cpp_template_ENABLE_USER_LINKER
      modern_cpp_template_ENABLE_SANITIZER_ADDRESS
      modern_cpp_template_ENABLE_SANITIZER_LEAK
      modern_cpp_template_ENABLE_SANITIZER_UNDEFINED
      modern_cpp_template_ENABLE_SANITIZER_THREAD
      modern_cpp_template_ENABLE_SANITIZER_MEMORY
      modern_cpp_template_ENABLE_UNITY_BUILD
      modern_cpp_template_ENABLE_CLANG_TIDY
      modern_cpp_template_ENABLE_CPPCHECK
      modern_cpp_template_ENABLE_COVERAGE
      modern_cpp_template_ENABLE_PCH
      modern_cpp_template_ENABLE_CACHE
      modern_cpp_template_ENABLE_SAMPLE_BASED_PROFILING
      modern_cpp_template_ENABLE_INSTRUMENTED_PROFILING
      modern_cpp_template_ENABLE_SIMD
      modern_cpp_template_ENABLE_NATIVE_ARCHITECTURE
      modern_cpp_template_ENABLE_DOXYGEN_WITH_CLANG)
  endif()

  modern_cpp_template_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (modern_cpp_template_ENABLE_SANITIZER_ADDRESS
                              OR modern_cpp_template_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(modern_cpp_template_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

# Setup the global options - effects modern_cpp_template targets as well as third party
# dependencies
macro(modern_cpp_template_global_options)
  if(modern_cpp_template_ENABLE_IPO)
    include(InterproceduralOptimization)
    modern_cpp_template_enable_ipo()
  endif()

  include(Profiling)
  if(modern_cpp_template_ENABLE_SAMPLE_BASED_PROFILING)
    modern_cpp_template_enable_sample_based_profiling()
  endif()
  if(modern_cpp_template_ENABLE_INSTRUMENTED_PROFILING)
    modern_cpp_template_enable_instrumented_profiling()
  endif()

  modern_cpp_template_supports_sanitizers()
endmacro()

# Setup the local options - only affects modern_cpp_template targets
macro(modern_cpp_template_local_options)
  # setup the fake targets that store the common compiler settings
  add_library(modern_cpp_template_warnings INTERFACE)
  add_library(modern_cpp_template::modern_cpp_template_warnings ALIAS modern_cpp_template_warnings)

  add_library(modern_cpp_template_options INTERFACE)
  add_library(modern_cpp_template::modern_cpp_template_options ALIAS modern_cpp_template_options)
  target_compile_features(modern_cpp_template_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

  if(PROJECT_IS_TOP_LEVEL)
    include(CompilerSettings)
  endif()

  include(CompilerWarnings)
  modern_cpp_template_set_project_warnings(modern_cpp_template_warnings)

  if(modern_cpp_template_ENABLE_USER_LINKER)
    include(Linker)
    configure_linker(modern_cpp_template_options)
  endif()

  include(Sanitizers)
  modern_cpp_template_enable_sanitizers(
    modern_cpp_template_options
    ${modern_cpp_template_ENABLE_SANITIZER_ADDRESS}
    ${modern_cpp_template_ENABLE_SANITIZER_LEAK}
    ${modern_cpp_template_ENABLE_SANITIZER_UNDEFINED}
    ${modern_cpp_template_ENABLE_SANITIZER_THREAD}
    ${modern_cpp_template_ENABLE_SANITIZER_MEMORY})

  if(modern_cpp_template_ENABLE_LIBPFM)
    find_package(PFM)
    if(HAVE_PFM)
      target_link_libraries(modern_cpp_template_options PRIVATE pfm)
    endif()
  endif()

  set_target_properties(modern_cpp_template_options PROPERTIES UNITY_BUILD ${modern_cpp_template_ENABLE_UNITY_BUILD})

  if(modern_cpp_template_ENABLE_PCH)
    target_precompile_headers(
      modern_cpp_template_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(modern_cpp_template_ENABLE_CACHE)
    include(CCache)
    modern_cpp_template_enable_cache()
  endif()

  include(StaticAnalyzers)
  if(modern_cpp_template_ENABLE_CLANG_TIDY)
    modern_cpp_template_enable_clang_tidy(modern_cpp_template_options)
  endif()

  if(modern_cpp_template_ENABLE_CPPCHECK)
    # Use Default CPPCHECK settings
    # otherwise pass in string of your own settings
    modern_cpp_template_enable_cppcheck("")
  endif()

  if(modern_cpp_template_ENABLE_COVERAGE)
    modern_cpp_template_enable_coverage(modern_cpp_template_options)
  endif()

  if(modern_cpp_template_BUILD_DOCUMENTATION)
    include(Doxygen)
    modern_cpp_template_enable_doxygen("")
  endif()

  check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
  if(LINKER_FATAL_WARNINGS)
    # This is not working consistently, so disabling for now
    # target_link_options(modern_cpp_template_options INTERFACE -Wl,--fatal-warnings)
  endif()

  if(modern_cpp_template_ENABLE_HARDENING)
    include(Hardening)
    if(NOT SUPPORTS_UBSAN
       OR modern_cpp_template_ENABLE_SANITIZER_UNDEFINED
       OR modern_cpp_template_ENABLE_SANITIZER_ADDRESS
       OR modern_cpp_template_ENABLE_SANITIZER_THREAD
       OR modern_cpp_template_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    modern_cpp_template_enable_hardening(modern_cpp_template_options ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
