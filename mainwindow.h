#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QDebug>

#include "widgets/imagewidget.h"
#include "widgets/imagefilewidget.h"
#include "services.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QImage img_;
    QGraphicsScene scene_;
    void resizeEvent(QResizeEvent *e);
};

#endif // MAINWINDOW_H
