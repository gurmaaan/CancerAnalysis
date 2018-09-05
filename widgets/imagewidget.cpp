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
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::on_actionZoom_In_triggered()
{
    //TODO scale ++
}

void ImageWidget::on_actionZoom_Out_triggered()
{
    //TODO scale--
}

void ImageWidget::on_zoomVSlider_sliderMoved(int position)
{
    //TODO changescale
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
    resizePlaceHolderImage(ui->imgGV->size());
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

    QGraphicsPixmapItem *emptyItem = new QGraphicsPixmapItem(QPixmap::fromImage(_img));
    _scene->addItem(emptyItem);
}

void ImageWidget::loadImg(QImage *img)
{
    setImg(*img);
}

void ImageWidget::resizePlaceHolderImage(int w, int h)
{
    if (w != 0 && h != 0)
    {
        QImage newPh = placeHolder(ui->imgGV->width(), ui->imgGV->height());
        setImg(newPh);
        _view->centerOn(0, 0);
    }
}

void ImageWidget::resizePlaceHolderImage(QSize size)
{
    if( size.width()!=0 && size.height() != 0)
    {
        resizePlaceHolderImage(size.width(), size.height());
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
    _h = h;
}

void ImageWidget::setW(int w)
{
    _w = w;
}

void ImageWidget::setName(const QString &name)
{
    _name = name;
}
