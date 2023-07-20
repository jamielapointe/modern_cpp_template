# Set default compiler warnings for a project
# Parameters:
#   TARGET_NAME [in] - the target name to set compiler warnings for
function(modern_cpp_template_set_project_warnings TARGET_NAME)
  set(MSVC_WARNINGS
      /W4 # Baseline reasonable warnings
      /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
      /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
      /w14263 # 'function': member function does not override any base class virtual member function
      /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
              # be destructed correctly
      /w14287 # 'operator': unsigned/negative constant mismatch
      /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
              # the for-loop scope
      /w14296 # 'operator': expression is always 'boolean_value'
      /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
      /w14545 # expression before comma evaluates to a function which is missing an argument list
      /w14546 # function call before comma missing argument list
      /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
      /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
      /w14555 # expression has no effect; expected expression with side- effect
      /w14619 # pragma warning: there is no warning number 'number'
      /w14640 # Enable warning on thread un-safe static member initialization
      /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
      /w14905 # wide string literal cast to 'LPSTR'
      /w14906 # string literal cast to 'LPWSTR'
      /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
      /permissive- # standards conformance mode for MSVC compiler.
      /WX)

  # Clang + GCC shared warnings
  set(CLANG_GCC_WARNINGS
      -Wall # enable standard diagnostics
      -Wextra # additional reasonable and standard diagnostics
      -Wshadow # warn the user if a variable declaration shadows one from a parent context
      -Wcast-align # warn for potential performance problem casts
      -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
                         # catch hard to track down memory errors
      -Wunused # warn on anything being unused
      -Wold-style-cast # warn for c-style casts
      -Woverloaded-virtual # warn if you overload (not override) a virtual function
      -Wpedantic # warn if non-standard C++ is used
      -Wconversion # warn on type conversions that may lose data
      -Wsign-conversion # warn on sign conversions
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wformat=2 # warn on security issues around functions that format output (ie printf)
      -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
      -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
      -Werror # Turn warnings into errors
      -Wfatal-errors # stop on the first error
  )

  # Clang only warnings
  set(CLANG_WARNINGS
      ${CLANG_GCC_WARNINGS}
      -Wshadow-all # warn the user if a variable declaration shadows one from a parent context - anywhere
      -Wlogical-op-parentheses # warn if '&&' within '||' without parenthesis
      -Wno-c++17-extensions # All C++17 only syntax
  )

  set(GCC_WARNINGS
      ${CLANG_GCC_WARNINGS}
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
      -Wuseless-cast # warn if you perform a cast to the same type
      -Wnull-dereference # warn if a null dereference is detected
  )

  set(CUDA_WARNINGS
      -Wall
      -Wextra
      -Wunused
      -Wconversion
      -Wshadow
      # TODO add more Cuda warnings
  )

  if(MSVC)
    set(PROJECT_WARNINGS_CXX ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_WARNINGS_CXX ${CLANG_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_WARNINGS_CXX ${GCC_WARNINGS})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for CXX compiler: '${CMAKE_CXX_COMPILER_ID}'")
    # TODO support Intel & other compilers
  endif()

  # use the same warning flags for C
  set(PROJECT_WARNINGS_C "${PROJECT_WARNINGS_CXX}")

  set(PROJECT_WARNINGS_CUDA "${CUDA_WARNINGS}")

  target_compile_options(
    ${TARGET_NAME}
    INTERFACE # C++ warnings
              $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_WARNINGS_CXX}>
              # C warnings
              $<$<COMPILE_LANGUAGE:C>:${PROJECT_WARNINGS_C}>
              # Cuda warnings
              $<$<COMPILE_LANGUAGE:CUDA>:${PROJECT_WARNINGS_CUDA}>)
endfunction()
