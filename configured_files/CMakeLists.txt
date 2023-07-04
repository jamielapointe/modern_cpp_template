# A very simple example of a configured file that might need to be
# converted to one that is publicly installed in the case that
# you are developing a library
configure_file("myproject_config.h.in" "${MYPROJECT_BUILD_ROOT}/configured_files/include/myproject_config.h"
               ESCAPE_QUOTES)
