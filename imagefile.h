#pragma once

#include <QString>
#include <QImage>

class ImageFile {
public:
    bool read(const QString &path);
    QImage toQImage(float scale = 1.0f, int brightness = 0, bool r = true, bool g = true, bool b = true) const;

    int size;
    int width;
    int height;
    int bpp;

private:
    QByteArray pixelData;
};
