#include "window.hpp"

#include <QFileDialog>
#include <QDebug>
#include "mambo.hpp"

mambo::gui::window::window() {
    using std::make_unique;

    centralWidget = make_unique<QWidget>();
    this->setCentralWidget(centralWidget.get());

    mainLayout = make_unique<QGridLayout>();
    centralWidget->setLayout(mainLayout.get());

    stateLabel = make_unique<QLabel>("-");
    stateLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    stateLabel->setFont(QFont("Arial", 12, QFont::Bold));
    mainLayout->addWidget(stateLabel.get(), 0, 0);

    buttonsLayout = make_unique<QHBoxLayout>();
    mainLayout->addLayout(buttonsLayout.get(), 1, 0);

    compressButton = make_unique<QPushButton>("Compress");
    buttonsLayout->addWidget(compressButton.get());
    connect(compressButton.get(), &QPushButton::clicked, this, &window::doCompress);

    uncompressButton = make_unique<QPushButton>("Uncompress", this);
    buttonsLayout->addWidget(uncompressButton.get());
    connect(uncompressButton.get(), &QPushButton::clicked, this, &window::doUncompress);

    this->show();
}

void mambo::gui::window::doCompress() {
    auto archive = QFileDialog::getSaveFileName();
    auto files = QFileDialog::getOpenFileNames();
    std::vector<std::string> vectorOfFiles(files.size());
    for(int i = 0; i < files.size(); ++i)
        vectorOfFiles[i] = files.at(i).toStdString();
    auto result = mambo::compress(archive.toStdString(), vectorOfFiles);
    if(result<0){
        stateLabel->setText("COMPRESS ERROR");
    } else {
        stateLabel->setText("COMPRESS RATIO: "+QString::number(result));
    }
}

void mambo::gui::window::doUncompress() {
    auto archive = QFileDialog::getOpenFileName();
    auto where = QFileDialog::getExistingDirectory();
    auto result = mambo::uncompress(archive.toStdString(), where.toStdString());
    if(result){
        stateLabel->setText("UNCOMPRESS ERROR");
    } else {
        stateLabel->setText("UNCOMPRESS SUCCESSFUL");
    }
}