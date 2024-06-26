#include <QApplication>
#include "core/window.hpp"
#include "mambo.hpp"
#include <iostream>

// TODO: add flag "-p/--path" for handle archive path

int main(int argc, char* argv[]){
    std::cout << mambo::compress("/home/xeim/temp/archive.mam", argc-1, const_cast<const char**>(argv+1));
    if(argc==1) {
        QApplication app(argc, argv);
        mambo::gui::window wnd;
        QApplication::exec();
    }
}
