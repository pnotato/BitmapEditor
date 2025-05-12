#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <QString>
#include <QImage>

class ImageFile {
public:
    bool read(const QString &path);
    QImage toQImage() const;

    int size;
    int width;
    int height;
    int bpp;

private:
    QByteArray pixelData;
};

#endif