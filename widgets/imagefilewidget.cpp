#include "imagefilewidget.h"
#include "ui_imagefilewidget.h"

ImageFileWidget::ImageFileWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

    name_ = "File ";
    path_ = QDir::currentPath();
    type_ = "";
    h_ = 0;
    w_ = 0;
    img_ = new QImage();
}

ImageFileWidget::~ImageFileWidget()
{
    delete ui;
}

void ImageFileWidget::setName(const QString &name)
{
    name_ = name;
    emit nameChanged(name_);
    setImgClass(name_);
    ui->imgNameField->setPlainText(name_);
    setTitle(name_);
}

void ImageFileWidget::setPath(const QString &path)
{
    QFileInfo fi(path);
    if(fi.exists())
    {
        path_ = path;
        emit pathChanged(path_);
        ui->pathLineEdit->setText(path);
        setName(FileService::fileName(path_));

        QString ext = FileService::fileExtension(path);
        if(ext != "")
            setType(ext);
    }
    else
    {
        QMessageBox::critical(this, Msg::header(MessageType::Error), Msg::body(ErrorType::FileNotExist));
        //TODO:: В зависимости от выбора пользоватнеля все закрыть или же переоткрыть диалог выбора
        //reopen file
    }
}

void ImageFileWidget::setType(const QString &ext)
{
    ui->typeCB->addItem(FileService::typeByExt(ext));
}

void ImageFileWidget::setImg(QImage *img)
{
    img_ = img;
    setH(img_->height());
    setW(img_->width());

    emit imgChanged(img_);
}

void ImageFileWidget::setImgClass(const QString &imgName)
{
    QString imgClass = StringService::getImageClass(imgName);
    if(StringService::notEmpty(imgClass))
        imgClass_ = imgClass;
    else
        imgClass_ = "Unknown class";
    ui->classCB->addItem(imgClass_);
}

void ImageFileWidget::setW(int w)
{
    w_ = w;
    ui->widthSpin->setMaximum(w);
    ui->widthSpin->setValue(w);

    emit wChanged(w);
}

void ImageFileWidget::setH(int h)
{
    h_ = h;
    ui->heightSpin->setMaximum(h);
    ui->heightSpin->setValue(h);

    emit hChanged(h);
}

void ImageFileWidget::on_actionOpen_Image_triggered()
{
    QFileDialog d(this);
    QString fp = FileService::initOpenImgFileDialog(d, QFileDialog::AcceptOpen);
    setPath(fp); //setPath + name + type + class
    img_ = new QImage(fp);
    setImg(img_); //setImg + w + h
}
