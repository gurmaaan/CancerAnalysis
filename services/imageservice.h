#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include <QColor>
#include <QPixmap>
#include <QImage>

class ImageService
{
public:
    ImageService();

    static QPixmap addRect(QPixmap &pm, int w = 1, QColor clr = QColor(Qt::black));
private:
    static bool borderArea(QImage img, int i, int j, int w = 1);
};

#endif // IMAGESERVICE_H
