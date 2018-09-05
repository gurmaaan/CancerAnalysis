#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QColor>

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

    QColor selectionClr() const;
    void setSelectionClr(const QColor &selectionClr);

    int thresholdVal() const;


public slots:
    void setImg(QImage *img);
    void setThresholdImg(QImage *thresholdImg);
    void setThresholdVal(int thresholdVal);

private slots:
    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_commandLinkButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QImage *img_;
    QGraphicsScene scene_;
    void connectAll();
    QImage *thresholdImg_;
    QColor selectionClr_;
    int thresholdVal_;
};

#endif // MAINWINDOW_H
