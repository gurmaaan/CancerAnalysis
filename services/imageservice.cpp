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
