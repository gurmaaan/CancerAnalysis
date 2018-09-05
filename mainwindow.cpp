#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectAll();
    QColor c = QColor(Qt::white);
    setSelectionClr(c);
    img_ = new QImage();
    thresholdImg_ = new QImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString temp = "";
    temp = FileService::projectDataPath();
    qDebug() << temp;
}

void MainWindow::connectAll()
{
    connect(ui->openImgFIleWidget, &ImageFileWidget::imgChanged,
            ui->imageView, &ImageWidget::loadImg);
    connect(ui->openImgFIleWidget, &ImageFileWidget::imgChanged,
            this, &MainWindow::setImg);

    connect(ui->openImgFIleWidget, &ImageFileWidget::nameChanged,
            ui->imageView, &ImageWidget::setName);

    connect(ui->imageView, &ImageWidget::selectionClrChanged,
            this, &MainWindow::setSelectionClr);
}

void MainWindow::setColorPoint(const QPoint colorPoint)
{
    colorPoint_ = colorPoint;
    QColor c = QColor(img_->pixelColor(colorPoint));
    setSelectionClr(c);
}

QImage *MainWindow::thresholdImg() const
{
    return thresholdImg_;
}

int MainWindow::thresholdVal() const
{
    return thresholdVal_;
}

void MainWindow::setThresholdVal(int thresholdVal)
{
    thresholdVal_ = thresholdVal;
    setThresholdImg(ImageService::threshold(img(), thresholdVal));
    //ui->imageView->loadImg(img());


}

void MainWindow::setThresholdImg(QImage *thresholdImg)
{
    thresholdImg_ = thresholdImg;
    ui->imageView->addScndLayer(thresholdImg_);
}

void MainWindow::setSelectionClr(const QColor &selectionClr)
{
    selectionClr_ = selectionClr;
    QPixmap pm = QPixmap( ui->selectionClrBtn->iconSize());
    pm.fill(selectionClr);
    pm = ImageService::addRect(pm);
    ui->selectionClrBtn->setIcon(QIcon(pm));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    setThresholdVal(value);
}

void MainWindow::on_commandLinkButton_clicked(bool checked)
{
    if(!checked)
        this->setCursor(Qt::CrossCursor);
    else
        this->setCursor(Qt::ArrowCursor);

}

QImage *MainWindow::img() const
{
    return img_;
}

void MainWindow::setImg(QImage *img)
{
    img_ = img;
}

void MainWindow::on_groupBox_clicked(bool checked)
{
    if(checked)
    {
        ui->imageView->loadImg(img());
        ui->imageView->addScndLayer(thresholdImg_);
    } else
    {
        ui->imageView->loadImg(img());
    }
}
