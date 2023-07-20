# The minimum CMake version must be >= 3.25 for the SYSTEM directory property
# to work.  We use this property to let clang-tidy know to ignore 3rd party
# software headers.
cmake_minimum_required(VERSION 3.25)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
set(CMAKE_CXX_STANDARD 20)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Require C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project name and language
project(
  modern_cpp_template
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C)

# Get the root directory of the modern_cpp_template
get_filename_component(modern_cpp_template_ROOT ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
get_filename_component(modern_cpp_template_BUILD_ROOT ${CMAKE_BINARY_DIR} ABSOLUTE)
get_filename_component(modern_cpp_template_INSTALL_ROOT ${CMAKE_INSTALL_PREFIX} ABSOLUTE)

# Append to the CMake Module path our custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${modern_cpp_template_ROOT}/cmake)

# Prevent the CMake Source and Build directories from being the same directory
include(PreventInSourceBuilds)

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()
include(ProjectOptions)
include(AddTargets)

#==============================================================================
# Setup user configurable CMake project options
#==============================================================================
modern_cpp_template_setup_options()

#==============================================================================
# Configure options that are enabled globally
#==============================================================================
modern_cpp_template_global_options()

#==============================================================================
# Configure 3rd party software
#==============================================================================
include(Dependencies)
modern_cpp_template_setup_dependencies()

#==============================================================================
# Configure options that are enabled locally
#==============================================================================
modern_cpp_template_local_options()

# don't know if this should be set globally from here or not...
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

#==============================================================================
# Set modern_cpp_template targets used in this project.
#
# This step does NOT add any sources to the targets.  Sources are added in the
# next step.  This includes executables, static & shared libraries, as well as
# object libraries, etc.
#==============================================================================
modern_cpp_template_add_targets()

#==============================================================================
# Add source directories
#==============================================================================

# configure files based on CMake configuration options
add_subdirectory(configured_files)

# Adding include
add_subdirectory(include)

# Adding the src:
add_subdirectory(src)

# Adding the tests
if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  add_subdirectory(test)
endif()
add_subdirectory(benchmark)

# Adding the fuzz tester
if(TARGET modern_cpp_template_fuzz_tester)
  message(STATUS "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if(NOT (modern_cpp_template_ENABLE_SANITIZER_ADDRESS OR modern_cpp_template_ENABLE_SANITIZER_UNDEFINED))
    message(WARNING "You need asan or ubsan enabled for meaningful fuzz testing")
  endif()
  add_subdirectory(fuzz_test)
endif()

#==============================================================================
# Link, install, and post-process all targets
#==============================================================================
modern_cpp_template_postprocess_targets()
