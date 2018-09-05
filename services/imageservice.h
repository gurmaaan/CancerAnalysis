#ifndef IMAGESERVIaCE_H
#define IMAGESERVICE_H

#include <QColor>
#include <QPixmap>
#include <QImage>
#include <QVector2D>
#include <QDebug>
#include "services/floatservice.h"

class ImageService
{
public:
    ImageService();

    static QPixmap addRect(QPixmap &pm, int w = 1, QColor clr = QColor(Qt::black));
    static QImage *threshold(QImage *img, int val);
    static bool colorRange(QColor test, QColor etalon, int percentage);
    static QVector<QPoint> selectWhiteArea(QImage *img, QImage *tr, QColor areaColor, QPoint startPoint);

    static int areaW(QVector<QPoint> areaPoints);
    static int areaH(QVector<QPoint> areaPoints);

private:
    static bool borderArea(QImage img, int i, int j, int w = 1);

};

#endif // IMAGESERVICE_H
