#include "mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    QPushButton *openButton = new QPushButton("Open BMP Image");
    metaLabel = new QLabel("Size: 0    Width: 0    Height: 0    BPP: 0");
    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(openButton);
    layout->addWidget(metaLabel);
    layout->addWidget(imageLabel);

    setCentralWidget(central);
    resize(800, 600);
 
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage);
}

void MainWindow::openImage() {
    QString path = QFileDialog::getOpenFileName(this, "Open BMP", "", "Bitmap Files (*.bmp)");
    if (path.isEmpty()) return;

    if (imageFile.read(path)) {
        QImage img = imageFile.toQImage();
        imageLabel->setPixmap(QPixmap::fromImage(img).scaled(600, 400, Qt::KeepAspectRatio));

        metaLabel->setText(QString("Size: %1    Width: %2    Height: %3    BPP: %4")
                               .arg(imageFile.size)
                               .arg(imageFile.width)
                               .arg(imageFile.height)
                               .arg(imageFile.bpp));
    }
}
