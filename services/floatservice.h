#ifndef FLOATSERVICE_H
#define FLOATSERVICE_H

#include <QObject>
#include <QVector>

class FloatService
{
public:
    FloatService();
    static bool equal(double d1, double d2, double epsilon = 0.0001);
    static bool equal(double d1, int i1, double epsilon = 0.0001);

    static double max(QVector<double> v);
    static double min(QVector<double> v);
    static double avr(QVector<double> v);

    static QString replaceCommaToPoint(QString *strWithComma);
    static double fromString(QString str);
};

#endif // FLOATSERVICE_H
