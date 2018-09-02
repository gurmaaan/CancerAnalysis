#include "floatservice.h"

FloatService::FloatService()
{

}

bool FloatService::equal(double d1, double d2, double epsilon)
{
    return qAbs(d1 - d2) < epsilon;
}

bool FloatService::equal(double d1, int i1, double epsilon)
{
    return ( qAbs( d1 - static_cast<double>(i1) ) < epsilon);
}

double FloatService::max(QVector<double> v)
{
    double maximum = 0;
    for(auto i : v)
    {
        if (i > maximum)
            maximum = i;
    }
    return  maximum;
}

double FloatService::min(QVector<double> v)
{
    double minimum = v.first();
    for(auto i : v)
    {
        if (i < minimum)
            minimum = i;
    }
    return  minimum;
}

double FloatService::avr(QVector<double> v)
{
    double sum = 0.0;
    for(int i = 0; i < v.count(); i++)
        sum+=v.at(i);

    double cnt = static_cast<double>( v .count() );
    return sum / cnt;
}

QString FloatService::replaceCommaToPoint(QString *strWithComma)
{
    return strWithComma->replace(",", ".");
}

double FloatService::fromString(QString str)
{
    str = replaceCommaToPoint(&str);
    bool successfullyConverted = false;
    double val = str.toDouble(&successfullyConverted);
    if(successfullyConverted)
        return val;
    else
        return 0.0;
}
