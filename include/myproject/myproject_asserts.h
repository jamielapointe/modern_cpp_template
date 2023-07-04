///@file myproject_asserts.h
///@author Jamie LaPointe (jamie.lapointe@gmail.com)
///@brief Provide some project level asserts
/// these asserts can be can be configured at compiled for certain behaviours
///@version 0.1
///@date 2023-07-02
///
///@copyright Copyright (c) 2023
///

// TODO(jlapointe) Perhaps provide some compile time options for handling and/or
// disabling error handling

#pragma once

#include <cassert>

#include "myproject_config.h"

namespace myproject {

///@brief This assert is meant for internal testing
/// By default this assert is disabled even in Debug mode and is meant for
/// internal library unit testing
///@param conditional_statement A boolean statement that must evaluate to true
/// to be valid
inline void myproject_internal_assert(bool conditional_statement) {
  if constexpr (myproject::options::enable_internal_debugging) {
    assert(conditional_statement);
  }
  static_cast<void>(conditional_statement);
}

///@brief Define our own runtime assert function
/// Currently just a wrapper around C assert.  However, depending on compile (or
/// runtime) options, this can be modified to have other behaviour for when a
/// condition check fails depending on the nature of the problem., such as
/// doing nothing, logging and error, raising exceptions, signaling, etc.
///@param conditional_statement
inline void myproject_assert(bool conditional_statement) {
  // for now this just translates to a simple cassert - this can be expanded to
  // either do nothing, throw optional/default exceptions, etc.
  assert(conditional_statement);
  static_cast<void>(conditional_statement);
}

}  // namespace myproject