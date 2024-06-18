#include <QApplication>
#include "core/window.hpp"
#include "mambo.hpp"

// TODO: add flag "-p/--path" for handle archive path

int main(int argc, char* argv[]){
    if(argc==1) {
        QApplication app(argc, argv);
        mambo::gui::window wnd;
        QApplication::exec();
    }
    mambo::compress(*argv, argc-1, const_cast<const char**>(argv+1));
}