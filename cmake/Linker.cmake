# Allow the user to select a user-configuralbe linker, such as lld, gold, bfd,
# or mold.
# Parameters:
#   TARGET_NAME [in] - The name of the target to use the custom linker
macro(modern_cpp_template_configure_linker TARGET_NAME)
  include(CheckCXXCompilerFlag)

  set(USER_LINKER_OPTION
      "lld"
      CACHE STRING "Linker to be used")
  set(USER_LINKER_OPTION_VALUES
      "lld"
      "gold"
      "bfd"
      "mold")
  set_property(CACHE USER_LINKER_OPTION PROPERTY STRINGS ${USER_LINKER_OPTION_VALUES})
  list(
    FIND
    USER_LINKER_OPTION_VALUES
    ${USER_LINKER_OPTION}
    USER_LINKER_OPTION_INDEX)

  if(${USER_LINKER_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom linker: '${USER_LINKER_OPTION}', explicitly supported entries are ${USER_LINKER_OPTION_VALUES}")
  endif()

  if(NOT ENABLE_USER_LINKER)
    return()
  endif()

  set(LINKER_FLAG "-fuse-ld=${USER_LINKER_OPTION}")

  check_cxx_compiler_flag(${LINKER_FLAG} CXX_SUPPORTS_USER_LINKER)
  if(CXX_SUPPORTS_USER_LINKER)
    target_compile_options(${TARGET_NAME} INTERFACE ${LINKER_FLAG})
  endif()
endmacro()
