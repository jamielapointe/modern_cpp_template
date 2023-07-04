# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#

find_package(fmt)

target_sources(myproject_fuzz_tester PUBLIC fuzz_tester.cpp)

target_link_libraries(myproject_fuzz_tester PRIVATE fmt::fmt -coverage -fsanitize=fuzzer)
target_compile_options(myproject_fuzz_tester PRIVATE -fsanitize=fuzzer)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME myproject_fuzz_tester_run COMMAND myproject_fuzz_tester -max_total_time=${FUZZ_RUNTIME})
