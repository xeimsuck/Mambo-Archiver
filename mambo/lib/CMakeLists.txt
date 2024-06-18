# mambo lib
file(GLOB_RECURSE mambo_source
        "source/*.h"
        "source/*.cpp"
)
add_library(mambo STATIC ${mambo_source})