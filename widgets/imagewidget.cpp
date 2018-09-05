#include "imagewidget.h"
#include "ui_imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::on_actionZoom_In_triggered()
{

}

void ImageWidget::on_actionZoom_Out_triggered()
{

}

void ImageWidget::on_zoomVSlider_sliderMoved(int position)
{

}
