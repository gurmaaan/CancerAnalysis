#ifndef STRINGSERVICE_H
#define STRINGSERVICE_H

#include <QString>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QObject>
#include <QTime>
#include <QDebug>

extern const QString _CSSBGCLR_;

class StringService : public QObject
{
    Q_OBJECT
public:
    explicit StringService(QObject *parent = nullptr);

    static QString getCornerString(QString fileText);
    static QString getTimeMessage(QTime t1, QTime t2, QString blockName = "");

    static QString changeCSSClrProp(QString stylesheetStr, QRgb newPropVal, QString cssPropName = _CSSBGCLR_);
    static QRgb getCSSClrProp(QString stylesheetStr, QString cssPropName);
    
    static QString getFirstCol(QString str);
    static QString getFirstRow(QString str);

    static QString multipleLineFromSingle(QString str, QString delimetr = "_", int strsCnt = 3);
    static QString singleLineFromMult(QString str);

    static QStringList splitAndRemoveFirstColOfFirstRow(QString fileText);
    static QStringList splitAndRemoveFirstRow(QString fileText);
    static QStringList splitBySemicolon(QString str);

    static bool notEmpty(QString str);

    static int maximumLen(QStringList list);

private:



};

#endif // STRINGSERVICE_H
