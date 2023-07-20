# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  check_cxx_compiler_flag(-fno-inline-functions, NO_INLINE_FUNCTIONS)
  if(NO_INLINE_FUNCTIONS)
    add_compile_options(-fno-inline-functions)
  endif()
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enhance error reporting and compiler messages
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  if(WIN32)
    # On Windows cuda nvcc uses cl and not clang
    add_compile_options($<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics> $<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>)
  else()
    add_compile_options(-fcolor-diagnostics)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(WIN32)
    # On Windows cuda nvcc uses cl and not gcc
    add_compile_options($<$<COMPILE_LANGUAGE:C>:-fdiagnostics-color=always>
                        $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>)
  else()
    add_compile_options(-fdiagnostics-color=always)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
  add_compile_options(/diagnostics:column)
else()
  message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

# run vcvarsall when msvc is used
include("${CMAKE_CURRENT_LIST_DIR}/VCEnvironment.cmake")
run_vcvarsall()

# Enable code coverage for a specific target
#   GCC uses the gcov tool: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
#   LLVM/Clang uses the Soruce-based Code Coverage:
#     https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
# Parameters:
#   TARGET_NAME [in] - The name of the target to enable code coverage for
function(modern_cpp_template_enable_coverage TARGET_NAME)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TARGET_NAME} INTERFACE --coverage -O0 -g)
    target_link_libraries(${TARGET_NAME} INTERFACE --coverage)
  endif()
  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(
      ${TARGET_NAME}
      INTERFACE -fprofile-instr-generate
                -fcoverage-mapping
                -O0
                -g)
    target_link_libraries(${TARGET_NAME} INTERFACE -fprofile-instr-generate -fcoverage-mapping)
  endif()
endfunction()

# Enable autovectorization - this is a bit platform dependent; but usually it requires -O3 and -ffast-math compiler options
# CMAKE_BUILD_TYPE "Release" enables -O3 by default.
function(modern_cpp_template_enable_autovectorization TARGET_NAME)
  if(NOT
     CMAKE_BUILD_TYPE
     STREQUAL
     "Release")
    message(FATAL_ERROR "You can only enable autovectorization if the CMAKE_BUILD_TYPE == 'Release'")
  endif()

  # currently only supporting this for GCC and LLVM/Clang
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(${TARGET_NAME} PRIVATE -ffast-math)
    if(modern_cpp_template_ENABLE_NATIVE_ARCHITECTURE)
      target_compile_options(${TARGET_NAME} PRIVATE -march=native)
    endif()
  endif()
endfunction()
