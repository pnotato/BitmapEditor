#include "imagefile.h"
#include <QFile>
#include <QtEndian>

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

QImage ImageFile::toQImage() const {
    if (bpp != 24) return QImage();

    QImage img(width, height, QImage::Format_RGB888);
    int rowSize = ((bpp * width + 31) / 32) * 4;

    for (int y = 0; y < height; ++y) {
        const uchar *row = (const uchar *)pixelData.constData() + (height - 1 - y) * rowSize;
        for (int x = 0; x < width; ++x) {
            img.setPixel(x, y, qRgb(row[x * 3 + 2], row[x * 3 + 1], row[x * 3 + 0]));
        }
    }

    return img;
}
