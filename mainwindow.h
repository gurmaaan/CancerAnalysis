#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QColor>
#include <QVector2D>

#include "services.h"
#include "widgets/imagewidget.h"
#include "widgets/imagefilewidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QColor selectionClr() { return selectionClr_;}
    int thresholdVal() const;
    QImage *img() const;
    QImage *thresholdImg() const;

    QVector<QPoint> getWhiteArea() const;

    void setWhiteArea(QVector<QPoint> value);

    QPoint getColorPoint() const;

public slots:
    void setImg(QImage *img);
    void setThresholdImg(QImage *thresholdImg);
    void setThresholdVal(int thresholdVal);
    void setColorPoint(const QPoint colorPoint);
    void setSelectionClr(const QColor &selectionClr);


private slots:
    void on_thresholdGB_clicked(bool checked);
    void on_selectionClrBtn_clicked(bool checked);

    void on_thresholdHSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QImage *img_;
    QGraphicsScene scene_;
    void connectAll();
    QImage *thresholdImg_;
    QColor selectionClr_;
    int thresholdVal_;
    QPoint colorPoint_;

    QVector<QPoint> whiteArea;
};

#endif // MAINWINDOW_H
