#include "imagewidget.h"
#include "ui_imagewidget.h"

const QString img_size_devider = " x ";

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    setView(ui->imgGV);
    _scene = new QGraphicsScene;
    _view->setScene(_scene);
    setImg(placeHolder());
    _sDouble = 1.000;
    _sInt = 1000;
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::on_actionZoom_In_triggered()
{
    _sDouble+=0.015;
    ui->zoomVSlider->setValue(_sInt);

    scaleTo(_sDouble);
}

void ImageWidget::on_actionZoom_Out_triggered()
{
    _sDouble-=0.015;
    ui->zoomVSlider->setValue(_sInt);
    scaleTo(_sDouble);
}

void ImageWidget::on_zoomVSlider_sliderMoved(int position)
{
    if(ui->zoomVSlider->value() != position)
    {
        //TODO::додумать зум по слайдеру
//        _sDouble = static_cast<double>(ui->zoomVSlider->value() / 1000);
//        scaleTo(_sDouble);
    }
}

QImage ImageWidget::placeHolder(int width, int height)
{
    QSize gvSize = QSize(width, height);
    QImage placeholderImg = QImage(gvSize, QImage::Format_Grayscale8);
    placeholderImg.fill(QColor(Qt::lightGray));

    QPainter p;
    p.begin(&placeholderImg);
    p.setPen(QPen(QPalette::Dark));
    p.setFont(QFont("Arial", 36, QFont::Bold));
    QString sizeText = QString::number(gvSize.width()) + img_size_devider + QString::number(gvSize.height());
    p.drawText(placeholderImg.rect(), Qt::AlignCenter, sizeText);
    p.end();

    return placeholderImg;
}

void ImageWidget::resizeEvent(QResizeEvent *e)
{
    if(ui->nameLE->text() == "")
        resizePhImg(ui->imgGV->size());
}

void ImageWidget::scaleTo(double newScaleKoeff)
{
    ui->zoomKoeffSB->setValue(_sDouble);
    _sInt = static_cast<int>(_sDouble * 1000);
    _view->scale(newScaleKoeff, newScaleKoeff);
    _view->centerOn(_scene->width() / 2, _scene->height() / 2);
}

void ImageWidget::mousePressEvent(QMouseEvent *e)
{
   QPoint p = QPoint(e->pos().x(), e->pos().y());
   setColorCoord(p);
   QColor newSelectionClr = img().pixelColor(p);
   setSelectionClr(newSelectionClr);
}

void ImageWidget::setImg(QImage img)
{
    if(img.isNull())
    {
        QImage emptyImg = placeHolder();
        _img = emptyImg;
    }
    else
        _img = img;

    ui->heightSpin->setValue(img.height());
    ui->widthSpin->setValue(img.width());
   // _scene->clear();
    QGraphicsPixmapItem *emptyItem = new QGraphicsPixmapItem(QPixmap::fromImage(_img));
    _scene->addItem(emptyItem);
}

void ImageWidget::loadImg(QImage *img)
{
    setImg(*img);
}

void ImageWidget::addScndLayer(QImage *scndLImg)
{
    _scene->clear();
    QGraphicsPixmapItem *firstItem = new QGraphicsPixmapItem(QPixmap::fromImage(_img));
    _scene->addItem(firstItem);
    QGraphicsPixmapItem *scndItem = new QGraphicsPixmapItem(QPixmap::fromImage(*scndLImg));
    _scene->addItem(scndItem);

}

void ImageWidget::resizePhImg(int w, int h)
{
    if (w != 0 && h != 0)
    {
        QImage newPh = placeHolder(ui->imgGV->width(), ui->imgGV->height());
        setImg(newPh);
        _view->centerOn(ui->imgGV->width() / 2, ui->imgGV->height() / 2);
    }
}

void ImageWidget::resizePhImg(QSize size)
{
    if( size.width()!=0 && size.height() != 0)
    {
        resizePhImg(size.width(), size.height());
    }
}

void ImageWidget::setView(QGraphicsView *view)
{
    _view = view;
}

void ImageWidget::setScene(QGraphicsScene *scene)
{
    _scene = scene;
}

void ImageWidget::setSInt(int sInt)
{
    _sInt = sInt;
}

void ImageWidget::setSDouble(double sDouble)
{
    _sDouble = sDouble;
}

void ImageWidget::setH(int h)
{
    if(h != 0 && h!=ui->heightSpin->value())
    {
        _h = h;
        ui->heightSpin->setValue(h);
    }
}

void ImageWidget::setW(int w)
{
    if(w != 0 && w!=ui->widthSpin->value())
    {
        _w = w;
        ui->heightSpin->setValue(w);
    }
}

void ImageWidget::setName(const QString &name)
{
    if(name != "" && name != ui->nameLE->text())
    {
        _name = name;
        ui->nameLE->setText(name);
    }
}

void ImageWidget::on_scndLayerOpacityHSlider_valueChanged(int value)
{
    qDebug() << _scene->items().count();
    double newOpacity = static_cast<double>(static_cast<double>(value) / static_cast<double>(100));
    qDebug() << newOpacity;
    if(_scene->items().count() >= 2)
        _scene->items().first()->setOpacity(newOpacity);

}

void ImageWidget::setSelectionClr(const QColor &selectionClr)
{
    selectionClr_ = selectionClr;
    emit selectionClrChanged(selectionClr);
}

void ImageWidget::setColorCoord(const QPoint &colorCoord)
{
    colorCoord_ = colorCoord;
    emit colorCoordChanged(colorCoord);
}
