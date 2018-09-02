#ifndef ITEMSSERVICE_H
#define ITEMSSERVICE_H

#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QColor>
#include <QFontMetrics>
#include <QPalette>

#include <services/floatservice.h>

class ItemsService : public QObject
{
    Q_OBJECT
public:
    explicit ItemsService(QObject *parent = nullptr);

    static void makeFontBold(QStandardItem *item);
    static void alignText(QStandardItem *item,  Qt::AlignmentFlag flag);

    static QStandardItem *fullCopy(QStandardItem* original);
    static QSize sizeOfOneSymb(QStandardItem *anyItem);
    static QSize sizeCorrection(QStandardItem *item);

    static void makeItemBGColor(QStandardItem *item, QColor color);
    static void makeAllItemBGColor(QStandardItemModel *model, QColor color);

    void makeItemTextColor(QStandardItem *item, QRgb colorCode);
    void makeAllItemsTextColor(QStandardItemModel *model, QRgb colorCode);

    static void changeBgColor(QStandardItem *item, QColor  color);
    static void changeBgColor(QStandardItem *item, QRgb colorCode);

    static void makeCheckable(QStandardItem  *item, bool state);
    static void addDescription(QStandardItem *item, QString text);

    static QString displayingStr(double data);

    static void makeHHeader(QStandardItem *item);
    static void makeVHeader(QStandardItem *item);
    static void makeHeader(QStandardItem *item, Qt::Orientation orientation);

    static QVector<double> getColVals(QStandardItemModel *m, int colNum);

signals:
    void sendStatusMessage(QString msgTxt);

public slots:
};

#endif // ITEMSSERVICE_H
