#ifndef MAMBO_GUI_WINDOW_HPP
#define MAMBO_GUI_WINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <memory>

namespace mambo::gui {
    class window final : public QMainWindow{
        Q_OBJECT
    public:
        window();

    public slots:
        void doCompress();
        void doUncompress();

    private:
        std::unique_ptr<QWidget> centralWidget = nullptr;
        std::unique_ptr<QGridLayout> mainLayout = nullptr;
        std::unique_ptr<QLabel> stateLabel = nullptr;
        std::unique_ptr<QHBoxLayout> buttonsLayout = nullptr;
        std::unique_ptr<QPushButton> compressButton = nullptr;
        std::unique_ptr<QPushButton> uncompressButton = nullptr;
    };
}

#endif //MAMBO_GUI_WINDOW_HPP
