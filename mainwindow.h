#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include "imagefile.h"

class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openImage();

private:
    QLabel *imageLabel;
    QLabel *metaLabel;
    ImageFile imageFile;
};

#endif