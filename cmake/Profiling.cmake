# More information on profile guided optimization(PGO):
# https://clang.llvm.org/docs/UsersManual.html#profile-guided-optimization

# Enable gprof sample based profiling
macro(modern_cpp_template_enable_sample_based_profiling)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    target_compile_options(${TARGET} PRIVATE -pg)
    target_link_libraries(${TARGET} PRIVATE -pg)
  endif()
endmacro()

# Enable intstrumented based profiling - Clang compiler only
macro(modern_cpp_template_enable_instrumented_profiling)
  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*")
    target_compile_options(${TARGET} PRIVATE -fprofile-instr-generate)
    target_link_libraries(${TARGET} PRIVATE -fprofile-instr-generate)
  endif()
endmacro()
