#ifndef SINGLE_AREA_H
#define SINGLE_AREA_H

#include <QVector>
#include <QPoint>


struct S_area
{
    quint64 id;
    QVector<QPoint> Points;
    QVector<QPoint> CPoints;
    S_area() = default;

    explicit S_area(quint64 number): id(number), Points(0), CPoints(0){}

    S_area& operator=(const S_area& obj)
    {
        id = obj.id;
        Points = obj.Points;
        CPoints = obj.CPoints;
        return *this;
    }

    void add_main(QPoint p)
    {
        Points.push_back(p);
    }

    void add_cont(QPoint p)
    {
        CPoints.push_back(p);
    }
};

#endif // SINGLE_AREA_H

