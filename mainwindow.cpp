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
    ui->thresholdGB->setChecked(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    connect(ui->imageView, &ImageWidget::colorCoordChanged,
            this, &MainWindow::setColorPoint);
}

QPoint MainWindow::getColorPoint() const
{
    return colorPoint_;
}

void MainWindow::setWhiteArea(QVector<QPoint> value)
{
    whiteArea = value;
}

QVector<QPoint> MainWindow::getWhiteArea() const
{
    return whiteArea;
}

void MainWindow::setColorPoint(const QPoint colorPoint)
{
    colorPoint_ = colorPoint;
    QColor areaClr = QColor(img_->pixelColor(colorPoint));
    setSelectionClr(areaClr);
    setWhiteArea(ImageService::selectWhiteArea(img(), thresholdImg(), areaClr, colorPoint));

    int aW = ImageService::areaW(whiteArea);
    int aH = ImageService::areaH(whiteArea);

    int S = aW * aH;
    int P = (aW+aH) * 2;
    int kF = P*P / S;
    ui->areaWhiteLineEdit->setText(QString::number(S / 1000));
    ui->perimetrWhiteLineEdit->setText(QString::number(P / 10));
    ui->formFactorWhiteLineEditr->setText(QString::number(kF));
    qDebug() << whiteArea.count();

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
    if(ui->thresholdHSlider->value() != thresholdVal)
        ui->thresholdHSlider->setValue(thresholdVal);

    if(ui->thresholdSB->value() != thresholdVal)
        ui->thresholdSB->setValue(thresholdVal);
    setThresholdImg(ImageService::threshold(img(), thresholdVal));
}

void MainWindow::setThresholdImg(QImage *thresholdImg)
{
    thresholdImg_ = thresholdImg;
    ui->imageView->addScndLayer(thresholdImg_);
}

void MainWindow::setSelectionClr(const QColor &selectionClr)
{
    ui->selectionClrBtn->setChecked(false);
    selectionClr_ = selectionClr;

    int trV = qGray(selectionClr_.rgb());
    qDebug() << trV;
    if(trV >= 0 && trV <= 255 && ui->imageView->name() != "")
       setThresholdVal(trV);
    ui->thresholdGB->setChecked(true);

    QPixmap pm = QPixmap( ui->selectionClrBtn->iconSize());
    pm.fill(selectionClr);
    pm = ImageService::addRect(pm);
    ui->selectionClrBtn->setIcon(QIcon(pm));
}

QImage *MainWindow::img() const
{
    return img_;
}

void MainWindow::setImg(QImage *img)
{
    img_ = img;
}

void MainWindow::on_thresholdGB_clicked(bool checked)
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

void MainWindow::on_selectionClrBtn_clicked(bool checked)
{
    if(!checked)
    {
//        setWhiteArea(ImageService::selectWhiteArea(img(), thresholdImg(), selectionClr(), getColorPoint()));
//        qDebug() << whiteArea;
    }
    else
    {

    }
}

void MainWindow::on_thresholdHSlider_valueChanged(int value)
{
    setThresholdVal(value);
}
