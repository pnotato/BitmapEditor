#include "mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QPushButton *openButton = new QPushButton("Open BMP Image");
    metaLabel = new QLabel("Size: 0    Width: 0    Height: 0    BPP: 0");
    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);

    scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setRange(1, 300);
    scaleSlider->setValue(100);

    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setRange(-100, 100);
    brightnessSlider->setValue(0);

    rCheck = new QCheckBox("Red");
    rCheck->setChecked(true);
    gCheck = new QCheckBox("Green");
    gCheck->setChecked(true);
    bCheck = new QCheckBox("Blue");
    bCheck->setChecked(true);

    QHBoxLayout *channelLayout = new QHBoxLayout();
    channelLayout->addWidget(rCheck);
    channelLayout->addWidget(gCheck);
    channelLayout->addWidget(bCheck);

    mainLayout->addWidget(openButton);
    mainLayout->addWidget(metaLabel);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(scaleSlider);
    mainLayout->addWidget(brightnessSlider);
    mainLayout->addLayout(channelLayout);

    setCentralWidget(central);
    resize(800, 600);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(scaleSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);
    connect(brightnessSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);
    connect(rCheck, &QCheckBox::stateChanged, this, &MainWindow::updateChannels);
    connect(gCheck, &QCheckBox::stateChanged, this, &MainWindow::updateChannels);
    connect(bCheck, &QCheckBox::stateChanged, this, &MainWindow::updateChannels);
}

void MainWindow::openImage() {
    QString path = QFileDialog::getOpenFileName(this, "Open BMP", "", "Bitmap Files (*.bmp)");
    if (path.isEmpty()) return;

    if (imageFile.read(path)) {
        metaLabel->setText(QString("Size: %1    Width: %2    Height: %3    BPP: %4")
                               .arg(imageFile.size)
                               .arg(imageFile.width)
                               .arg(imageFile.height)
                               .arg(imageFile.bpp));
        updateImage();
    }
}

void MainWindow::updateImage() {
    float scale = scaleSlider->value() / 100.0f;
    int brightness = brightnessSlider->value();
    QImage img = imageFile.toQImage(scale, brightness, rCheck->isChecked(), gCheck->isChecked(), bCheck->isChecked());
    imageLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::updateChannels() {
    updateImage();
}