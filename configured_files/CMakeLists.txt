# A very simple example of a configured file that might need to be
# converted to one that is publicly installed in the case that
# you are developing a library
configure_file("modern_cpp_template_config.h.in"
               "${modern_cpp_template_BUILD_ROOT}/configured_files/include/modern_cpp_template_config.h" ESCAPE_QUOTES)
