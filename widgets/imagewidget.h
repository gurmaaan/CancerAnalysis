#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

private slots:
    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();


    void on_zoomVSlider_sliderMoved(int position);

private:
    Ui::ImageWidget *ui;
};

#endif // IMAGEWIDGET_H
