include(CheckCXXCompilerFlag)

# Enable hardening (stack protection, etc.)
#
# Parameters:
#   TARGET                [in] - The name of the TARGET_NAME to be built
#   GLOBAL                [in] - If true, then apply the settings globally or
#                                only to the passed in target
#   UBSAN_MINIMAL_RUNTIME [in] - Enable the undefined behavior minimal runtime
#                                that is suitable for the production
#                                environment.
#                                https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
macro(modern_cpp_template_enable_hardening TARGET_NAME UBSAN_MINIMAL_RUNTIME)
  message(STATUS "** Enabling Hardening (Target ${TARGET_NAME}) **")

  if(MSVC)
    target_compile_options(${TARGET_NAME} INTERFACE /sdl /DYNAMICBASE /guard:cf)
    message(STATUS "*** MSVC flags: /sdl /DYNAMICBASE /guard:cf /NXCOMPAT /CETCOMPAT")
    target_link_options(
      ${TARGET_NAME}
      INTERFACE
      /NXCOMPAT
      /CETCOMPAT)

  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang|GNU")
    target_compile_definitions(${TARGET_NAME} INTERFACE -D_GLIBCXX_ASSERTIONS)
    message(STATUS "*** GLIBC++ Assertions (vector[], string[], ...) enabled")

    target_compile_options(${TARGET_NAME} INTERFACE -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3)
    message(STATUS "*** g++/clang _FORTIFY_SOURCE=3 enabled")

    check_cxx_compiler_flag(-fstack-protector-strong STACK_PROTECTOR)
    if(STACK_PROTECTOR)
      target_compile_options(${TARGET_NAME} INTERFACE -fstack-protector-strong)
      message(STATUS "*** g++/clang -fstack-protector-strong enabled")
    else()
      message(STATUS "*** g++/clang -fstack-protector-strong NOT enabled (not supported)")
    endif()

    check_cxx_compiler_flag(-fcf-protection CF_PROTECTION)
    if(CF_PROTECTION)
      target_compile_options(${TARGET_NAME} INTERFACE -fcf-protection)
      message(STATUS "*** g++/clang -fcf-protection enabled")
    else()
      message(STATUS "*** g++/clang -fcf-protection NOT enabled (not supported)")
    endif()

    check_cxx_compiler_flag(-fstack-clash-protection CLASH_PROTECTION)
    if(CLASH_PROTECTION)
      if(LINUX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${TARGET_NAME} INTERFACE -fstack-clash-protection)
        message(STATUS "*** g++/clang -fstack-clash-protection enabled")
      else()
        message(STATUS "*** g++/clang -fstack-clash-protection NOT enabled (clang on non-Linux)")
      endif()
    else()
      message(STATUS "*** g++/clang -fstack-clash-protection NOT enabled (not supported)")
    endif()
  endif()

  if(${UBSAN_MINIMAL_RUNTIME})
    check_cxx_compiler_flag(-fsanitize=undefined UBSAN)
    check_cxx_compiler_flag(-fsanitize-minimal-runtime SANITIZE_MINIMAL_RUNTIME)
    check_cxx_compiler_flag(-fno-sanitize-recover=undefined NO_SANITIZE_RECOVER_UNDEFINED)
    if(UBSAN AND SANITIZE_MINIMAL_RUNTIME)
      target_compile_options(${TARGET_NAME} INTERFACE -fsanitize=undefined -fsanitize-minimal-runtime)
      target_link_options(
        ${TARGET_NAME}
        INTERFACE
        -fsanitize=undefined
        -fsanitize-minimal-runtime)

      if(NO_SANITIZE_RECOVER_UNDEFINED)
        target_compile_options(${TARGET_NAME} INTERFACE -fno-sanitize-recover=undefined)
        target_link_options(${TARGET_NAME} INTERFACE -fno-sanitize-recover=undefined)
      else()
        message(STATUS "** not enabling -fno-sanitize-recover=undefined")
      endif()

      message(STATUS "*** ubsan minimal runtime enabled")
    else()
      message(STATUS "*** ubsan minimal runtime NOT enabled (not supported)")
    endif()
  else()
    message(STATUS "*** ubsan minimal runtime NOT enabled (not requested)")
  endif()
endmacro()
