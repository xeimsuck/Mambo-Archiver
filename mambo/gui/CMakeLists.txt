# mambo gui
file(GLOB_RECURSE mambo-gui_source
        "source/*.h"
        "source/*.cpp"
)
add_executable(mambo-gui ${mambo-gui_source})
target_include_directories(mambo-gui PRIVATE source)
set_target_properties(mambo-gui PROPERTIES AUTOMOC TRUE)
## link mambo
target_link_libraries(mambo-gui mambo)
target_include_directories(mambo-gui PRIVATE "../lib/source")
## link QT6
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
target_link_libraries(mambo-gui Qt6::Core Qt6::Gui Qt6::Widgets)