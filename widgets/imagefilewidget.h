#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QGroupBox>
#include <QStandardPaths>
#include <QMessageBox>
#include "services.h"

namespace Ui {
class FileWidget;
}

class ImageFileWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit ImageFileWidget(QWidget *parent = nullptr);
    ~ImageFileWidget();

    inline QString name() { return name_; }
    inline QString path() const { return path_; }
    inline int h() const { return h_; }
    inline int w() const { return w_; }
    inline QImage* img() const { return img_; }
    inline QString imgClass() const { return imgClass_; }

public slots:
    void setName(const QString &name);
    void setPath(const QString &path);
    void setType(const QString &ext);
    void setImg(QImage *img);
    void setImgClass(const QString &imgName);
    void setW(int w);
    void setH(int h);

signals:
   void pathChanged(QString newPath);
   void nameChanged(QString fileName);
   void wChanged(int newCnt);
   void hChanged(int newCnt);
   void imgChanged(QImage *newImg);

private slots:
   void on_actionOpen_Image_triggered();

private:
    Ui::FileWidget *ui;
    QString name_;
    QString type_;
    QString path_;
    int h_;
    int w_;
    QImage *img_;
    QString imgClass_;
};

#endif // FILEWIDGET_H
