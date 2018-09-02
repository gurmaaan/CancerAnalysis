#include "stringservice.h"

const QString _CSSBGCLR_ = "background-color";

StringService::StringService(QObject *parent) :
    QObject(parent)
{
}

QString StringService::getCornerString(QString fileText)
{
    return getFirstCol(getFirstRow(fileText));
}

QString StringService::getTimeMessage(QTime t1, QTime t2, QString blockName)
{
    int tms1 = t1.second() * 1000 + t1.msec();
    int tms2 = t2.second() * 1000 + t2.msec();
    QString msgTxt = tr("Block \"") + blockName + tr("\" finished in ") + QString::number(tms2 - tms1) + tr(" milliseconds");
    return msgTxt;
}

QString StringService::changeCSSClrProp(QString stylesheetStr, QRgb newPropVal, QString cssPropName)
{
    QString newCSSStr = "";
    QStringList cssPropList = stylesheetStr.split(";");
    foreach (QString prop, cssPropList)
    {
        QStringList propNameValList = prop.split(":");
        QString propName = propNameValList.first().replace(" ", "");
        QString propVal = (propName == cssPropName) ?
                          QColor(newPropVal).name() :
                          propNameValList.last().replace(" ", "");
        newCSSStr += (propName + ":" + propVal + ";");
        qDebug() << newCSSStr;
    }
    return newCSSStr;
}

QRgb StringService::getCSSClrProp(QString stylesheetStr, QString cssPropName)
{
    QRgb clrCode = QColor(255,255,255).rgb();
    QStringList stylePartdsList = stylesheetStr.split(";");
    for(QString clrPart : stylePartdsList)
    {
        QStringList paramWithVal = clrPart.split(":");
        if(paramWithVal.first().replace(" ", "") == cssPropName)
        {
            QString btnClrStr = paramWithVal.last();
            if(btnClrStr.contains("rgb("))// rgb(100, 100, 100)
            {
                btnClrStr.replace(" ", ""); //rgb(100,100,100)
                btnClrStr.replace("rgb(", ""); //100,100,100)
                btnClrStr.replace(")", ""); //100,100,100

                int clrCompnts[3];
                QStringList components = btnClrStr.split(",");
                bool compInt = false;

                if(components.count() == 3)
                {
                    for(int i = 0; i < components.count() ; i++)
                        clrCompnts[i] = components.at(i).toInt(&compInt);
                }
                QColor btnClr = QColor(clrCompnts[0], clrCompnts[1], clrCompnts[2]).isValid();

                if(compInt && (components.count() == 3) && btnClr.isValid())
                {
                    clrCode = btnClr.rgb();
                    break;
                }
            } else if (btnClrStr.contains("#")) {
                if(QColor(btnClrStr).isValid())
                    clrCode = QColor(btnClrStr).rgb();
            }
            else
                clrCode = QColor(Qt::red).rgb();
        }
    }
    return clrCode;
}



bool StringService::notEmpty(QString str)
{
    if (str == "" || str == " ")
        return false;
    else
        return true;
}

int StringService::maximumLen(QStringList list)
{
    int max = 0;
    foreach(QString str, list)
    {
        if(str.length() > max)
            max = str.length();
    }
    return max;
}

QStringList StringService::splitAndRemoveFirstColOfFirstRow(QString fileText)
{
    QString first = getFirstRow(fileText);
    QStringList list = first.split(";");
    list.removeFirst();
    return list;
}

QStringList StringService::splitAndRemoveFirstRow(QString fileText)
{
    QStringList list = fileText.split("\n");
    list.removeFirst();
    return list;
}

QStringList StringService::splitBySemicolon(QString str)
{
    return str.split(";");
}

QString StringService::getFirstCol(QString str)
{
    return str.split(";").first();
}

QString StringService::getFirstRow(QString str)
{
    return str.split("\n").first();
}

QString StringService::multipleLineFromSingle(QString str, QString delimetr, int strsCnt)
{
    //TODO:: сделать ф-ю универсальной
    int midPos = str.count(delimetr) / 2 + 1;
    int lastPos = str.count(delimetr);
    int cnt = 0;
    QStringList list = str.split(delimetr);
    QString multipleString = "";
    if(list.count() != 0)
    {
        for(QString item : list)
        {
            cnt++;
            if (  (cnt==midPos) || ( (strsCnt==3) && (cnt==lastPos) )  )
                multipleString+=(item+"\n");
            else if(cnt == list.count())
                multipleString+=item;
            else
                multipleString+=(item+delimetr);
        }
        str = multipleString;
    }
    else
        qDebug() << "Input string \"" << str << "\" doesn't contain delimetr \"" << delimetr << "\"";

    return str;
}

QString StringService::singleLineFromMult(QString str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str.at(i) == "\n")
            str.replace(i, 1, " ");
    }

    return str;
}
