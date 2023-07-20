if(TARGET modern_cpp_template_benchmark)
  target_sources(modern_cpp_template_benchmark PUBLIC benchmark_main.cpp bm_fibonacci.cpp)

  # target_compile_options(modern_cpp_template_benchmark PRIVATE -fno-exceptions)
  target_compile_options(modern_cpp_template_benchmark PRIVATE -Wno-weak-vtables)
  target_compile_options(modern_cpp_template_benchmark PRIVATE -Wno-global-constructors)
  target_compile_options(modern_cpp_template_benchmark PRIVATE -Wno-unused-member-function)

  target_include_directories(modern_cpp_template_benchmark SYSTEM PRIVATE "${benchmark_SOURCE_DIR}/include")

  target_link_system_libraries(modern_cpp_template_benchmark PRIVATE benchmark::benchmark)
endif()
