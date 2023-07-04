include(CompilerSettings)

# Add a target to the specific target list in addition to the common target lists
# Parameters:
#   TARGET_NAME [in]     - name of the target to add to the lists
#   TARGET_LIST [in/out] - The specific target list to add the target to in
#                          addition to the "all" target lists
function(myproject_add_target_to_list TARGET_NAME TARGET_LIST)
  set(LOCAL TARGET_LIST ${${TARGET_LIST}})
  get_target_property(TARGET_TYPE ${TARGET_NAME} TYPE)

  if(TARGET_TYPE STREQUAL "EXECUTABLE")
    list(APPEND ALL_EXECUTABLE_TARGETS_LIST ${TARGET_NAME})
  endif()

  set(INSTALLABLE_LIST
      EXECUTABLE
      STATIC_LIBRARY
      MODULE_LIBRARY
      SHARED_LIBRARY)
  list(
    FIND
    INSTALLABLE_LIST
    ${TARGET_TYPE}
    INSTALLABLE_IDX)
  if(INSTALLABLE_IDX GREATER -1)
    list(APPEND ALL_INSTALLABLE_TARGETS_LIST ${TARGET_NAME})
  endif()

  list(APPEND ALL_TARGETS_LIST ${TARGET_NAME})
  list(APPEND LOCAL_TARGET_LIST ${TARGET_NAME})

  # Add the locally modified lists to the parent scope (e.g. the callers scope)
  # Recall the functions have local scope, while macros have no scope of their own
  set(${TARGET_LIST}
      ${LOCAL_TARGET_LIST}
      PARENT_SCOPE)
  set(ALL_TARGETS_LIST
      ${ALL_TARGETS_LIST}
      PARENT_SCOPE)
  set(ALL_EXECUTABLE_TARGETS_LIST
      ${ALL_EXECUTABLE_TARGETS_LIST}
      PARENT_SCOPE)
  set(ALL_INSTALLABLE_TARGETS_LIST
      ${ALL_INSTALLABLE_TARGETS_LIST}
      PARENT_SCOPE)
endfunction()

# Add common includes to all targets
# Parameters: <none>
macro(myproject_add_common_includes)
  foreach(TARGET_NAME IN LISTS ALL_TARGETS_LIST)
    target_include_directories(${TARGET_NAME} PUBLIC ${MYPROJECT_ROOT}/include)
    target_include_directories(${TARGET_NAME} PUBLIC ${MYPROJECT_BUILD_ROOT}/configured_files/include)
    #target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${gsl_SOURCE_DIR}/include)
  endforeach()
endmacro()

macro(myproject_add_compiler_optimizations)
  if(CMAKE_BUILD_TYPE STREQUAL "Release" AND myproject_ENABLE_SIMD)
    foreach(TARGET_NAME IN LISTS ALL_TARGETS_LIST)
      myproject_enable_autovectorization(${TARGET_NAME})
    endforeach()
  endif()
endmacro()

# Add all targets used in this project
# Parameters: <none>
macro(myproject_add_targets)
  set(ALL_EXECUTABLE_TARGETS_LIST "")
  set(ALL_INSTALLABLE_TARGETS_LIST "")
  set(ALL_TARGETS_LIST "")
  set(PRIMARY_APP_LIST "")
  set(TEST_LIST "")

  add_executable(myproject_sample_app)
  add_executable(myproject::myproject_sample_app ALIAS myproject_sample_app)
  myproject_add_target_to_list(myproject_sample_app PRIMARY_APP_LIST)

  if(PROJECT_IS_TOP_LEVEL AND myproject_BUILD_FUZZ_TESTS)
    add_executable(myproject_fuzz_tester)
    add_executable(myproject::myproject_fuzz_tester ALIAS myproject_fuzz_tester)
    myproject_add_target_to_list(myproject_fuzz_tester TEST_LIST)
  endif()

  if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
    add_executable(myproject_benchmark)
    add_executable(myproject::myproject_benchmark ALIAS myproject_benchmark)
    myproject_add_target_to_list(myproject_benchmark TEST_LIST)
  endif()

  myproject_add_common_includes()
  myproject_add_compiler_optimizations()
endmacro()

# Postprocess all targets (e.g., link, install, etc.)
macro(myproject_postprocess_targets)
  # find_package(fmt REQUIRED)
  # find_package(quill REQUIRED)
  # find_package(CLI11 REQUIRED)

  foreach(TARGET_NAME IN LISTS ALL_TARGETS_LIST)
    target_link_system_libraries(${TARGET_NAME} PRIVATE fmt::fmt)
    target_link_system_libraries(${TARGET_NAME} PRIVATE quill::quill)
    target_link_system_libraries(${TARGET_NAME} PRIVATE Microsoft.GSL::GSL)
    target_link_system_libraries(${TARGET_NAME} PRIVATE absl::base)
    target_link_system_libraries(${TARGET_NAME} PRIVATE absl::hash)
    target_link_libraries(${TARGET_NAME} PRIVATE myproject::myproject_options)
    target_link_libraries(${TARGET_NAME} PRIVATE myproject::myproject_warnings)
  endforeach()

  target_link_system_libraries(myproject_sample_app PRIVATE CLI11::CLI11)

  # Don't go any further if we're not top level
  if(NOT PROJECT_IS_TOP_LEVEL)
    return()
  endif()

  # If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
  # so that it behaves well with MSVC's debugger, and we can run the target from visual studio
  if(MSVC)
    get_all_installable_targets(all_targets)
    message("all_targets=${all_targets}")
    set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
  endif()

  # set the startup project for the "play" button in MSVC
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT intro)

  if(CMAKE_SKIP_INSTALL_RULES)
    return()
  endif()

  include(PackageProject)

  # Experience shows that explicit package naming can help make it easier to sort
  # out potential ABI related issues before they start, while helping you
  # track a build to a specific GIT SHA
  set(CPACK_PACKAGE_FILE_NAME
      "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
  )

  include(CPack)
endmacro()
