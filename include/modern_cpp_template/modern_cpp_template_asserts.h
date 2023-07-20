///\file modern_cpp_template_asserts.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Provide some project level asserts
/// these asserts can be can be configured at compiled for certain behaviours
///\version 0.1
///\date 2023-07-02
///
///\copyright Copyright (c) 2023
///

// TODO(jlapointe) Perhaps provide some compile time options for handling and/or
// disabling error handling

// this is currently using ugly C style macros until we discover a better way...

#pragma once

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "modern_cpp_template/system_constants.h"

namespace modern_cpp_template::internal {

inline void print_error(char const* const expression, char const* const file,
                        uint32_t line, char const* const function,
                        char const* const message) {
  // Print to stderr and abort, as specified in <cassert>.
  spdlog::critical("Assertion failed at {}:{} in {}: {}; message = {}\n",
                   file == nullptr ? "<file>" : file, line,
                   function == nullptr ? "<function>" : function, expression,
                   message == nullptr ? "" : message);
}

// Generic default assert handler.
template <typename EnableIf = void, typename... EmptyArgs>
struct assert_handler_impl {
  static inline void run(char const* const expression, char const* const file,
                         uint32_t line, char const* const function,
                         char const* const message) {
    print_error(expression, file, line, function, message);
    std::abort();
  }
};

// Use POSIX __assert_fail handler when available.
//
// This allows us to integrate with systems that have custom handlers.
//
// NOTE: this handler is not always available on all POSIX systems (otherwise
// we could simply test for __unix__ or similar).  The handler function name
// seems to depend on the specific toolchain implementation, and differs between
// compilers, platforms, OSes, etc.  Hence, we detect support via SFINAE.
template <typename... EmptyArgs>
struct assert_handler_impl<
    std::void_t<decltype(__assert_fail(
        static_cast<char const*>(nullptr),  // expression
        static_cast<char const*>(nullptr),  // file
        0,                                  // line
        static_cast<char const*>(nullptr),  // function
        std::declval<EmptyArgs>()...  // Empty substitution required for SFINAE.
        ))>,
    EmptyArgs...> {
  static inline void run(char const* const expression, char const* const file,
                         uint32_t line, char const* const function,
                         char const* const message) {
    print_error(expression, file, line, function, message);
    // GCC requires this call to be dependent on the template parameters.
    __assert_fail(expression, file, line, function,
                  std::declval<EmptyArgs>()...);
  }
};

///\internal Define our own runtime assert function
///\param expression String representation of the expression
///\param file Source file where assert occurred
///\param line Line number where assert occurred
///\param function Function where assert occurred
///\param message Optional error message
inline void _assert_handler(char const* const expression,
                            char const* const file, uint32_t line,
                            char const* const function,
                            char const* const message) {
  assert_handler_impl<>::run(expression, file, line, function, message);
}

///\internal This assert is meant for internal testing
///\param expression String representation of the expression
///\param file Source file where assert occurred
///\param line Line number where assert occurred
///\param function Function where assert occurred
///\param message Optional error message
inline void _internal_assert_handler(char const* const expression,
                                     char const* const file, uint32_t line,
                                     char const* const function,
                                     char const* const message) {
  if constexpr (modern_cpp_template::options::kEnableInternalDebugging) {
    _assert_handler(expression, file, line, function, message);
  }
}

}  // namespace modern_cpp_template::internal
