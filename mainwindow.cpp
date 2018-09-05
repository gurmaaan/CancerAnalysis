#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectAll();
    setSelectionClr(QColor(Qt::white));
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
}

void MainWindow::setThresholdImg(QImage *thresholdImg)
{
    thresholdImg_ = thresholdImg;
}

QColor MainWindow::selectionClr() const
{
    return selectionClr_;
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

}

void MainWindow::on_commandLinkButton_clicked(bool checked)
{
    if(checked)
        setCursor(Qt::CrossCursor);
    else
        setCursor(Qt::ArrowCursor);

}

void MainWindow::setImg(QImage *img)
{
    img_ = img;
}
