function(myproject_enable_coverage project_name)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${project_name} INTERFACE --coverage -O0 -g)
    target_link_libraries(${project_name} INTERFACE --coverage)
  endif()
  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    # enable Clang Source-based Code Coverage
    # https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
    target_compile_options(
      ${project_name}
      INTERFACE -fprofile-instr-generate
                -fcoverage-mapping
                -O0
                -g)
    target_link_libraries(${project_name} INTERFACE -fprofile-instr-generate -fcoverage-mapping)
  endif()
endfunction()
