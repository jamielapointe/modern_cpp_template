# Enable dynamic analysis sanitizers; list of sanitizers
#   ASAN - Address Sanitizer - https://clang.llvm.org/docs/AddressSanitizer.html
#   LSAN - Leak Sanitizer - https://clang.llvm.org/docs/LeakSanitizer.html
#   UBSAN - Undefined Behavior Sanitizer: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
#   TSAN - Thread Sanitizer: https://clang.llvm.org/docs/ThreadSanitizer.html
#   MSAN - Memory Sanitizer: https://clang.llvm.org/docs/MemorySanitizer.html
#
# Parameters:
#   TARGET                              [in] - The name of the target to be built
#   ENABLE_SANITIZER_ADDRESS            [in] - Enable ASAN
#   ENABLE_SANITIZER_LEAK               [in] - Enable LSAN
#   ENABLE_SANITIZER_UNDEFINED_BEHAVIOR [in] - Enable UBSAN
#   ENABLE_SANITIZER_THREAD             [in] - Enable TSAN
#   ENABLE_SANITIZER_MEMORY             [in] - Enable MSAN
function(
  modern_cpp_template_enable_sanitizers
  TARGET_NAME
  ENABLE_SANITIZER_ADDRESS
  ENABLE_SANITIZER_LEAK
  ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
  ENABLE_SANITIZER_THREAD
  ENABLE_SANITIZER_MEMORY)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(SANITIZERS "")

    if(${ENABLE_SANITIZER_ADDRESS})
      list(APPEND SANITIZERS "address")
    endif()

    if(${ENABLE_SANITIZER_LEAK})
      list(APPEND SANITIZERS "leak")
    endif()

    if(${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR})
      list(APPEND SANITIZERS "undefined")
    endif()

    if(${ENABLE_SANITIZER_THREAD})
      if("address" IN_LIST SANITIZERS OR "leak" IN_LIST SANITIZERS)
        message(WARNING "Thread sanitizer does not work with Address and Leak sanitizer enabled")
      else()
        list(APPEND SANITIZERS "thread")
      endif()
    endif()

    if(${ENABLE_SANITIZER_MEMORY} AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
      message(
        WARNING
          "Memory sanitizer requires all the code (including libc++) to be MSan-instrumented otherwise it reports false positives"
      )
      if("address" IN_LIST SANITIZERS
         OR "thread" IN_LIST SANITIZERS
         OR "leak" IN_LIST SANITIZERS)
        message(WARNING "Memory sanitizer does not work with Address, Thread or Leak sanitizer enabled")
      else()
        list(APPEND SANITIZERS "memory")
      endif()
    endif()
  elseif(MSVC)
    if(${ENABLE_SANITIZER_ADDRESS})
      list(APPEND SANITIZERS "address")
    endif()
    if(${ENABLE_SANITIZER_LEAK}
       OR ${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR}
       OR ${ENABLE_SANITIZER_THREAD}
       OR ${ENABLE_SANITIZER_MEMORY})
      message(WARNING "MSVC only supports address sanitizer")
    endif()
  endif()

  list(
    JOIN
    SANITIZERS
    ","
    LIST_OF_SANITIZERS)

  if(LIST_OF_SANITIZERS)
    if(NOT
       "${LIST_OF_SANITIZERS}"
       STREQUAL
       "")
      if(NOT MSVC)
        target_compile_options(${TARGET_NAME} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        target_link_options(${TARGET_NAME} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        if(${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR})
          target_compile_options(${TARGET_NAME} INTERFACE -fno-sanitize-recover=all)
          target_link_options(${TARGET_NAME} INTERFACE -fno-sanitize-recover=all)
        endif()
      else()
        string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
        if("${index_of_vs_install_dir}" STREQUAL "-1")
          message(
            SEND_ERROR
              "Using MSVC sanitizers requires setting the MSVC environment before building the project. Please manually open the MSVC command prompt and rebuild the project."
          )
        endif()
        target_compile_options(${TARGET_NAME} INTERFACE /fsanitize=${LIST_OF_SANITIZERS} /Zi /INCREMENTAL:NO)
        target_compile_definitions(${TARGET_NAME} INTERFACE _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
        target_link_options(${TARGET_NAME} INTERFACE /INCREMENTAL:NO)
      endif()
    endif()
  endif()

endfunction()
