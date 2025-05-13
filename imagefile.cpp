#include "imagefile.h"
#include <QFile>
#include <QtEndian>
#include <algorithm>

bool ImageFile::read(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return false;
    QByteArray data = file.readAll();
    if (data.size() < 54 || data.mid(0, 2) != "BM") return false;

    size = qFromLittleEndian<quint32>((const uchar*)data.constData() + 2);
    int offset = qFromLittleEndian<quint32>((const uchar*)data.constData() + 10);
    width = qFromLittleEndian<qint32>((const uchar*)data.constData() + 18);
    height = qFromLittleEndian<qint32>((const uchar*)data.constData() + 22);
    bpp = qFromLittleEndian<quint16>((const uchar*)data.constData() + 28);

    pixelData = data.mid(offset);
    return true;
}

QImage ImageFile::toQImage(float scale, int brightness, bool r, bool g, bool b) const {
    if (bpp != 24) return QImage();

    int newWidth = std::max(1, int(width * scale));
    int newHeight = std::max(1, int(height * scale));
    QImage img(newWidth, newHeight, QImage::Format_RGB888);
    int rowSize = ((bpp * width + 31) / 32) * 4;

    for (int y = 0; y < newHeight; ++y) {
        int srcY = std::min(int(y / scale), height - 1);
        const uchar *row = (const uchar *)pixelData.constData() + (height - 1 - srcY) * rowSize;

        for (int x = 0; x < newWidth; ++x) {
            int srcX = std::min(int(x / scale), width - 1);
            const uchar *pixel = row + srcX * 3;

            int red = r ? std::clamp(int(pixel[2]) + brightness, 0, 255) : 0;
            int green = g ? std::clamp(int(pixel[1]) + brightness, 0, 255) : 0;
            int blue = b ? std::clamp(int(pixel[0]) + brightness, 0, 255) : 0;

            img.setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return img;
}
