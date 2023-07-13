if(TARGET myproject_benchmark)
  target_sources(myproject_benchmark PUBLIC benchmark_main.cpp bm_fibonacci.cpp)

  # target_compile_options(myproject_benchmark PRIVATE -fno-exceptions)
  target_compile_options(myproject_benchmark PRIVATE -Wno-weak-vtables)
  target_compile_options(myproject_benchmark PRIVATE -Wno-global-constructors)
  target_compile_options(myproject_benchmark PRIVATE -Wno-unused-member-function)

  target_include_directories(myproject_benchmark SYSTEM PRIVATE "${benchmark_SOURCE_DIR}/include")

  target_link_system_libraries(myproject_benchmark PRIVATE benchmark::benchmark)
endif()
