# Enable doxygen doc builds of source
# Parameters:
#   DOXYGEN_THEME [in] - Optional theme for Doxygen generation
function(myproject_enable_doxygen DOXYGEN_THEME)
  # If not specified, use the top readme file as the first page
  if((NOT DOXYGEN_USE_MDFILE_AS_MAINPAGE) AND EXISTS "${PROJECT_SOURCE_DIR}/README.md")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
  endif()

  # set better defaults for doxygen
  is_verbose(_is_verbose)
  if(NOT ${_is_verbose})
    set(DOXYGEN_QUIET YES)
  endif()
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  # svg files are much smaller than jpeg and png, and yet they have higher quality
  set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  set(DOXYGEN_DOT_TRANSPARENT YES)
  set(DOXYGEN_WARN_AS_ERROR YES)

  # If not specified, exclude the vcpkg files and the files CMake downloads under _deps (like project_options)
  if(NOT DOXYGEN_EXCLUDE_PATTERNS)
    set(DOXYGEN_EXCLUDE_PATTERNS
        "${PROJECT_BINARY_DIR}/*"
        "${PROJECT_SOURCE_DIR}/out/*"
        "${PROJECT_SOURCE_DIR}/third_party/*"
        "${PROJECT_SOURCE_DIR}/tools/*")
  endif()

  if("${DOXYGEN_THEME}" STREQUAL "")
    set(DOXYGEN_THEME "awesome-sidebar")
  endif()

  if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
    # use a modern doxygen theme
    # https://github.com/jothepro/doxygen-awesome-css v1.6.1
    FetchContent_Declare(_doxygen_theme
                         URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v1.6.1.zip)
    FetchContent_MakeAvailable(_doxygen_theme)
    if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
      set(DOXYGEN_HTML_EXTRA_STYLESHEET "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome.css")
    endif()
    if("${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
      set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css")
    endif()
  else()
    # use the original doxygen theme
  endif()

  # add doxygen-docs target
  message(STATUS "Adding `doxygen-docs` target that builds the documentation.")
  doxygen_add_docs(doxygen-docs ALL ${PROJECT_SOURCE_DIR}
                   COMMENT "Generating documentation - entry file: ${CMAKE_CURRENT_BINARY_DIR}/html/index.html")
endfunction()
