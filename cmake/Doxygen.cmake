# Enable doxygen doc builds of source
# Parameters:
#   DOXYGEN_THEME [in] - Optional theme for Doxygen generation
function(modern_cpp_template_enable_doxygen DOXYGEN_THEME)
  # set better defaults for doxygen
  # is_verbose(_is_verbose)
  # if(NOT ${_is_verbose})
  #   set(DOXYGEN_QUIET YES)
  # endif()
  set(DOXYGEN_PROJECT_NAME "${PROJECT_NAME}")
  set(DOXYGEN_PROJECT_NUMBER "${PROJECT_VERSION}")
  set(DOXYGEN_PROJECT_BRIEF "${PROJECT_DESCRIPTION}")
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_GENERATE_TREEVIEW YES)

  # ONLY set this flag to true if you linked the clang library into doxygen.
  # This should be the same version of clang you are compiling your code with.
  # This is useful for getting better parsing of C++ code.
  if(${modern_cpp_template_ENABLE_DOXYGEN_WITH_CLANG})
    set(DOXYGEN_CLANG_ASSISTED_PARSING YES)
    set(DOXYGEN_CLANG_ADD_INC_PATHS NO)
    set(DOXYGEN_CLANG_OPTIONS "-w -Wno-error")
    set(DOXYGEN_CLANG_DATABASE_PATH "${CMAKE_BINARY_DIR}")
  endif()

  # svg files are much smaller than jpeg and png, and yet they have higher quality
  set(DOXYGEN_HAVE_DOT YES)
  set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  set(DOXYGEN_DOT_TRANSPARENT YES)

  set(DOXYGEN_QUITE NO)
  set(DOXYGEN_WARN_NO_PARAMDOC YES)
  set(DOXYGEN_WARN_AS_ERROR YES)

  set(DOXYGEN_USE_MATHJAX YES)
  set(DOXYGEN_MATHJAX_VERSION MathJax_3)
  set(DOXYGEN_MATHJAX_FORMAT chtml)
  set(DOXYGEN_MATHJAX_RELPATH https://cdn.jsdelivr.net/npm/mathjax@3)
  # set(DOXYGEN_MATHJAX_EXTENSIONS "require ams physics mathtools colorv2 boldsymbol")

  if("${DOXYGEN_THEME}" STREQUAL "")
    set(DOXYGEN_THEME "awesome-sidebar")
  endif()

  set(DOXYGEN_HTML_EXTRA_STYLESHEET "")
  if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")

    set(DOXYGEN_HTML_HEADER "${PROJECT_SOURCE_DIR}/docs/doxygen_custom/custom_header.html")
    set(DOXYGEN_HTML_FOOTER "${PROJECT_SOURCE_DIR}/docs/doxygen_custom/custom_footer.html")

    # use a modern doxygen theme
    # https://github.com/jothepro/doxygen-awesome-css v2.2.1
    FetchContent_Declare(_doxygen_theme
                         URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.2.1.zip)
    FetchContent_MakeAvailable(_doxygen_theme)
    if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
      set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome.css")
    endif()
    set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                      "${PROJECT_SOURCE_DIR}/docs/doxygen_custom/custom.css")
    if("${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
      set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css")
      set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css")
    endif()
    set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                      "${PROJECT_SOURCE_DIR}/docs/doxygen_custom/custom_alternative.css")

    # set the javascript
    set(DOXYGEN_HTML_EXTRA_FILES
        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js"
        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js"
        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-paragraph-link.js"
        "${_doxygen_theme_SOURCE_DIR}/doxygen-custom/toggle-alternative-theme.js"
        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-interactive-toc.js"
        "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-tabs.js")

    # Required Doxygen settings for the theme
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_DISABLE_INDEX YES)
    set(DOXYGEN_FULL_SIDEBAR NO)
    # make it look a bit nicer
    set(DOXYGEN_HTML_COLORSTYLE_HUE 209)
    set(DOXYGEN_HTML_COLORSTYLE_SAT 255)
    set(DOXYGEN_HTML_COLORSTYLE_GAMMA 113)
  else()
    # use the original doxygen theme
  endif()

  # add doxygen-docs target
  message(STATUS "Adding `doxygen-docs` target that builds the documentation.")
  file(
    GLOB_RECURSE INCLUDE_LIST
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/include/*.h" "${PROJECT_SOURCE_DIR}/include/*.hxx" "${PROJECT_SOURCE_DIR}/include/*.hpp")
  file(
    GLOB_RECURSE SRC_LIST
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hxx"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.C"
    "${PROJECT_SOURCE_DIR}/src/*.cc"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.cxx")
  list(
    APPEND
    DOC_LIST
    ${INCLUDE_LIST}
    ${SRC_LIST})

  doxygen_add_docs(
    doxygen-docs ${DOC_LIST} "${PROJECT_SOURCE_DIR}/docs/mainpage.md"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Generating documentation - entry file: ${CMAKE_CURRENT_BINARY_DIR}/html/index.html")
endfunction()
