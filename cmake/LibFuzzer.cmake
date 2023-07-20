# Test for libfuzzer
# More information: https://llvm.org/docs/LibFuzzer.html
# Parameters:
#   var_name [out] - True if libfuzzer is available; else False
function(modern_cpp_template_check_libfuzzer_support var_name)
  set(LibFuzzerTestSource
      "
#include <cstdint>

extern \"C\" int LLVMFuzzerTestOneInput(const std::uint8_t *data, std::size_t size) {
  return 0;
}
    ")

  include(CheckCXXSourceCompiles)

  set(CMAKE_REQUIRED_FLAGS "-fsanitize=fuzzer")
  set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=fuzzer")
  check_cxx_source_compiles("${LibFuzzerTestSource}" ${var_name})

endfunction()
