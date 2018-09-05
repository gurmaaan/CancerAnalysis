#include "imageservice.h"

ImageService::ImageService()
{

}

QPixmap ImageService::addRect(QPixmap &pm, int w, QColor clr)
{
    QImage img = QImage(pm.toImage());
    QColor baseClr = img.pixelColor(pm.width() / 2, pm.height() / 2);

    for (int i = 0; i < img.height(); i++) {
        for (int j = 0; j < img.width(); j++)
        {
            if(borderArea(img, i, j, w))
                img.setPixelColor(j,i, clr);
            else
                img.setPixelColor(j, i, baseClr);
        }
    }

    pm = QPixmap::fromImage(img);
    return pm;
}

QImage *ImageService::threshold(QImage *img, int val)
{
    QImage *trImg = new QImage(img->size(), QImage::Format_Grayscale8);
    for (int i = 0; i < img->width(); i++) {
        for (int j = 0; j < img->height(); j++)
        {
            int grVal = qGray(img->pixelColor(i, j).rgb());
            if(grVal <= val)
                trImg->setPixelColor(i, j, QColor(Qt::black));
            else
                trImg->setPixelColor(i, j, QColor(Qt::white));
        }
    }
    return trImg;
}

bool ImageService::colorRange(QColor test, QColor etalon, int percentage)
{
    int eR = qRed(etalon.rgb());
    int eG = qGreen(etalon.rgb());
    int eB = qBlue(etalon.rgb());

    double koeff = static_cast<double>(static_cast<double>(percentage) / static_cast<double>(100));

    int eRMin = eR - static_cast<int>(eR*koeff);
    eRMin = (eRMin >= 0) ? eRMin : 0;
    int eGMin = eG - static_cast<int>(eG*koeff);
    eGMin = (eGMin >= 0) ? eGMin : 0;
    int eBMin = eB - static_cast<int>(eB*koeff);
    eBMin = (eBMin >= 0) ? eBMin : 0;

    int eRMax = eR + static_cast<int>(eR*koeff);
    eRMax = (eRMax <= 255) ? eRMax : 255;
    int eGMax = eG + static_cast<int>(eG*koeff);
    eGMax = (eGMax <= 255) ? eGMax : 255;
    int eBMax = eB + static_cast<int>(eB*koeff);
    eBMax = (eBMax <= 255) ? eBMax : 255;

    int tR = qRed(test.rgb());
    int tG = qGreen(test.rgb());
    int tB = qBlue(test.rgb());

    bool cROk = false;
    bool cGOk = false;
    bool cBOk = false;

    if(tR >= eRMin && tR <= eRMax)
        cROk = true;
    if(tG >= eGMin && tG <= eGMax)
        cGOk = true;
    if(tB >= eBMin && tB <= eBMax)
        cBOk = true;

    return cROk && cGOk && cBOk;
}

QVector<QPoint> ImageService::selectWhiteArea(QImage *img, QImage *tr, QColor areaColor, QPoint startPoint)
{
    QVector<QPoint> areaPoints;

    //вправо вверх
    for (int i = startPoint.x(); i < img->width(); i++)
    {
        for (int j = startPoint.y(); j >=0; j--)
        {
            if( colorRange(img->pixelColor(i,j), areaColor, 5))
            {
                QPoint p = QPoint(i, j);
                areaPoints.append(p);
            }
        }
    }

    for(int i = startPoint.x(); i >= 0; i--)
    {
        for(int j = startPoint.y(); j < img->height(); j++)
        {
            if( colorRange(img->pixelColor(i,j), areaColor, 5))
            {
                QPoint p = QPoint(i, j);
                areaPoints.append(p);
            }
        }
    }
    return areaPoints;
}

int ImageService::areaW(QVector<QPoint> areaPoints)
{
    QVector<int> xV;
    for(auto p : areaPoints)
        xV << p.x();

    int lx = FloatService::min(xV);
    int rx = FloatService::max(xV);

    int w = rx - lx;
    if(w >= 0)
        return w;
    else
        return -w;
}

int ImageService::areaH(QVector<QPoint> areaPoints)
{
    QVector<int> yV;
    for(auto p : areaPoints)
        yV << p.y();

    int tY = FloatService::min(yV);
    int bY = FloatService::max(yV);

    int h = bY - tY;
    if(h >= 0)
        return h;
    else
        return -h;

}

bool ImageService::borderArea(QImage img, int i, int j, int w)
{
    bool top = false;
    bool bot = false;
    bool lef = false;
    bool rig = false;
    bool res = false;

    top = ( (i>=img.height()-1-w) && (i<=img.height()-1) );
    bot = ( (j>=img.width() -1-w) && (j<=img.width() -1) );
    lef = ( (j>=0) && (j<=w) );
    rig = ( (i>=0) && (i<=w) );

    res = top || bot || lef || rig;
    return res;

}
