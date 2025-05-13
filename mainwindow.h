#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "imagefile.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openImage();
    void updateImage();
    void updateChannels();

private:
    QLabel *imageLabel;
    QLabel *metaLabel;
    QSlider *scaleSlider;
    QSlider *brightnessSlider;
    QCheckBox *rCheck;
    QCheckBox *gCheck;
    QCheckBox *bCheck;
    ImageFile imageFile;
};

#endif 