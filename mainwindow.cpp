#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openImgFIleWidget, &ImageFileWidget::imgChanged,
            ui->imageView, &ImageWidget::loadImg);
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
