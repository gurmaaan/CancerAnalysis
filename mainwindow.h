#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "services.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

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
};

#endif // MAINWINDOW_H
