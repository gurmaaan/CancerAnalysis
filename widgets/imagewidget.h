#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

extern const QString img_size_devider;

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    inline int 	sInt() 	    const { return _sInt; 	}
    inline double sDouble() const { return _sDouble;}
    inline int 	h() 	    const { return _h; 		}
    inline int 	w() 	    const { return _w; 		}
    inline QString name()   const { return _name; 	}
    inline QImage img()     const { return _img;    }


public slots:
    void setName(const QString &name);
    void setW(int w);
    void setH(int h);
    void setSDouble(double sDouble);
    void setSInt(int sInt);
    void setScene(QGraphicsScene *scene);
    void setView(QGraphicsView *view);
    void setImg(QImage img);
    void loadImg(QImage *img);

private slots:
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_zoomVSlider_sliderMoved(int position);

private:
    Ui::ImageWidget *ui;

    QImage _img;
    QString _name;
    int _w;
    int _h;

    double _sDouble;
    int _sInt;

    QGraphicsScene *_scene;
    QGraphicsView *_view;

    //---------

    QImage placeHolder();
};

#endif // IMAGEWIDGET_H
