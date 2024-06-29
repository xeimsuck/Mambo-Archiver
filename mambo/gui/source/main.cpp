#include <QApplication>
#include <iostream>

#include "core/window.hpp"
#include "mambo.hpp"

constexpr std::string_view HELP_OUTPUT =
R"(UI:
    [argc]  [description]
    0       GUI mode (or use flag "-g")
    1+      console mode
FLAGS:
    [short] [long]          [description]
    -c      --compress      compress files to archive
            STRUCTURE:      ARCHIVE FILE1 [FILE2...]
    -u      --uncompress    uncompress archive to directory
            STRUCTURE:      ARCHIVE WHERE
    -g      --gui           run gui mode
RETURN CODES:
    [code]  [description]
    0       successful
    -1      error
)";


int runGUI(int& argc, char* argv[]){
    QApplication app(argc, argv);
    mambo::gui::window wnd;
    return QApplication::exec();
}

int main(int argc, char* argv[]){
    if(argc==1) return runGUI(argc, argv);

    int i = 1;
    std::string flag = argv[i++];

    if(flag == "-g" || flag == "--gui"){
        return runGUI(argc, argv);
    }
    else if(flag == "-h" || flag == "--help"){
        std::cout << HELP_OUTPUT;
    }
    else if(flag == "-c" || flag == "--compress"){
        std::string archive = argv[i++];
        std::vector<std::string> files;

        while (i<argc) files.emplace_back(argv[i++]);

        auto ratio = mambo::compress(archive,  files);
        if(ratio<0){
            std::cout << "COMPRESS ERROR\n";
            return 1;
        }
        std::cout << "COMPRESSION RATIO: " << ratio << "\n";
    } else if (flag == "-u" || flag == "--uncompress"){
        std::string archive = argv[i++];
        std::string where = argv[i++];

        auto result = mambo::uncompress(archive, where);
        if(result){
            std::cout << "UNCOMPRESS ERROR\n";
            return 1;
        }
    } else {
        std::cout << "UNKNOWN FLAG: " << flag<< "\nUSE --help\n";
        return 1;
    }
    return 0;
}
