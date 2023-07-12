///@file macros.h
///@author Jamie LaPointe (jamie.lapointe@gmail.com)
///@brief Provides macros and other preprocessor directives to the rest of the
/// project
///@version 0.1
///@date 2023-07-05
///
///@copyright Copyright (c) 2023
///

// this uses macros... yuck.  Until I discover a better way of doing this
// stuff...

#pragma once

#include "myproject/compiler_macros.h"
#include "myproject/myproject_asserts.h"

/// \internal MYPROJECT_HAS_BUILTIN determine is a __builtin_expression is
/// available
#if defined(__has_builtin)
#  define MYPROJECT_HAS_BUILTIN(expression) __has_builtin(expression)
#else
#  define MYPROJECT_HAS_BUILTIN(expression) 0
#endif

#ifndef MYPROJECT_HAS_BUILTIN_FILE
// Clang can check if __builtin_FILE() is supported.
// GCC > 5, MSVC 2019 14.26 (1926) all have __builtin_FILE().
//
// For NVCC, it's more complicated.  Through trial-and-error:
//   - nvcc+gcc supports __builtin_FILE() on host, and on device after CUDA 11.
//   - nvcc+msvc supports __builtin_FILE() only after CUDA 11.
#  if (MYPROJECT_HAS_BUILTIN(__builtin_FILE) &&                             \
       (MYPROJECT_COMP_CLANG || !defined(MYPROJECT_CUDA_ARCH))) ||          \
      (MYPROJECT_GNUC_STRICT_AT_LEAST(5, 0, 0) &&                           \
       (MYPROJECT_COMP_NVCC >= 110000 || !defined(MYPROJECT_CUDA_ARCH))) || \
      (MYPROJECT_COMP_MSVC >= 1926 &&                                       \
       (!MYPROJECT_COMP_NVCC || MYPROJECT_COMP_NVCC >= 110000))
#    define MYPROJECT_HAS_BUILTIN_FILE 1
#  else
#    define MYPROJECT_HAS_BUILTIN_FILE 0
#  endif
#endif  // MYPROJECT_HAS_BUILTIN_FILE

#if MYPROJECT_HAS_BUILTIN_FILE
#  define MYPROJECT_BUILTIN_FILE __builtin_FILE()
#  define MYPROJECT_BUILTIN_LINE __builtin_LINE()
#else
// Default (potentially unsafe) values.
#  define MYPROJECT_BUILTIN_FILE __FILE__
#  define MYPROJECT_BUILTIN_LINE __LINE__
#endif

// Use __PRETTY_FUNCTION__ when available, since it is more descriptive, as
// __builtin_FUNCTION() only returns the undecorated function name.
// This should still be okay ODR-wise since it is a compiler-specific fixed
// value.  Mixing compilers will likely lead to ODR violations anyways.
#if MYPROJECT_COMP_MSVC
#  define MYPROJECT_BUILTIN_FUNCTION static_cast<char const *>(__FUNCSIG__)
#elif MYPROJECT_COMP_GNUC
#  define MYPROJECT_BUILTIN_FUNCTION \
    static_cast<char const *>(__PRETTY_FUNCTION__)
#else
#  define MYPROJECT_BUILTIN_FUNCTION static_cast<char const *>(__func__)
#endif

// clang-format off

// We must define functional macros because as of C++ 20 there is no way to
// perform stringification on an expression other than via a the C preprocessor

#if !defined(_MYPROJECT_ASSERT_MESSAGE_DEFINITION)
#  define _MYPROJECT_ASSERT_MESSAGE_DEFINITION(expression, message)           \
    {                                                                         \
      if (expression) [[likely]] {                                            \
        static_cast<void>(0);                                                 \
      }                                                                       \
      else {                                                                  \
        myproject::internal::_assert_handler(                                 \
                 #expression, MYPROJECT_BUILTIN_FILE, MYPROJECT_BUILTIN_LINE, \
                 MYPROJECT_BUILTIN_FUNCTION, message);                        \
      }                                                                       \
    }
#endif

#if !defined(_MYPROJECT_INTERNAL_ASSERT_MESSAGE_DEFINITION)
#  define _MYPROJECT_INTERNAL_ASSERT_MESSAGE_DEFINITION(expression, message)  \
    {                                                                         \
      if (expression) [[likely]] {                                            \
        static_cast<void>(0);                                                 \
      }                                                                       \
      else {                                                                  \
        myproject::internal::_internal_assert_handler(                        \
                 #expression, MYPROJECT_BUILTIN_FILE, MYPROJECT_BUILTIN_LINE, \
                 MYPROJECT_BUILTIN_FUNCTION, message);                        \
      }                                                                       \
    }
#endif

///\brief macro function to run-time error check an expression with a custom error message
#if !defined(myproject_assert_message)
#  define myproject_assert_message(expression, message) _MYPROJECT_ASSERT_MESSAGE_DEFINITION(expression, message);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\brief macro function to run-time error check an expression
#if !defined(myproject_assert)
#  define myproject_assert(expression) myproject_assert_message(expression, nullptr);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\internal macro function to run-time error check an expression with a custom error message
#if !defined(myproject_internal_assert_message)
#  define myproject_internal_assert_message(expression, message) _MYPROJECT_INTERNAL_ASSERT_MESSAGE_DEFINITION(expression, message);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\internal macro function to run-time error check an expression
#if !defined(myproject_internal_assert)
#  define myproject_internal_assert(expression) myproject_internal_assert_message(expression, nullptr);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

// clang-format on
