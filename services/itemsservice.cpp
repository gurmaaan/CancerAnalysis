#include "itemsservice.h"

ItemsService::ItemsService(QObject *parent) : QObject(parent)
{

}

void ItemsService::makeAllItemsTextColor(QStandardItemModel *model, QRgb colorCode)
{
    for(int c = 0; c < model->columnCount(); c++)
        for(int r = 0; r < model->rowCount(); r++)
            makeItemTextColor(model->item(r,c), colorCode);
}

void ItemsService::makeItemTextColor(QStandardItem *item, QRgb colorCode)
{
    item->setData(QColor(colorCode), Qt::TextColorRole);
}

void ItemsService::makeItemBGColor(QStandardItem *item, QColor color)
{
    //Вылет при вызове этой функции
    item->setData(QBrush(color, Qt::DiagCrossPattern), Qt::BackgroundColorRole);
}

void ItemsService::makeAllItemBGColor(QStandardItemModel *model, QColor color)
{
    for(int c = 0; c < model->columnCount(); c++)
        for(int r = 0; r < model->rowCount(); r++)
            makeItemBGColor(model->item(r, c), color);
}

void ItemsService::makeFontBold(QStandardItem *item)
{
    item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
}

QSize ItemsService::sizeOfOneSymb(QStandardItem *anyItem)
{
    QFont itemFont(anyItem->font().family(), anyItem->font().pointSize());
    QFontMetrics fm(itemFont);
    int w = fm.width("W");
    int h = fm.height();
    return QSize(w,h);
}

QSize ItemsService::sizeCorrection(QStandardItem *item)
{
    QSize newSize = sizeOfOneSymb(item);
    //BUG: колхозненькое определение необходимой ширины, переделать чтобы красиво было
    newSize.setWidth( newSize.width() * static_cast<int>(item->text().length() * 0.50) );
    newSize.setHeight( newSize.height() * 4) ;
    item->setSizeHint(newSize);
    return newSize;
}

void ItemsService::alignText(QStandardItem *item, Qt::AlignmentFlag flag)
{
    item->setTextAlignment(Qt::Alignment(flag));
    item->setData(flag, Qt::TextAlignmentRole);
}

QStandardItem *ItemsService::fullCopy(QStandardItem *original)
{
    QStandardItem *item = new QStandardItem();
    if(original != nullptr)
    {
        item->setData( original->data(Qt::EditRole) );
        item->setData( original->data(Qt::BackgroundRole) );
        item->setData( original->data(Qt::TextAlignmentRole));
        item->setData( original->data(Qt::TextColorRole));
        item->setData( original->data(Qt::DisplayPropertyRole));
        item->setData( original->data(Qt::DisplayRole));
    } else
    {
        item->setData( "NULL");
    }
    return item;
}

void ItemsService::changeBgColor(QStandardItem *item, QColor color)
{
    QBrush brush(color, Qt::Dense5Pattern);
    item->setBackground(brush);
}
void ItemsService::changeBgColor(QStandardItem *item, QRgb colorCode)
{
    QBrush brush(QColor(colorCode), Qt::Dense7Pattern);
    item->setBackground(brush);
}

void ItemsService::makeCheckable(QStandardItem *item, bool state)
{
    item->setEditable(state);
    item->setSelectable(state);
    item->setCheckable(state);
    Qt::CheckState checkState = state ? Qt::Checked : Qt::Unchecked;
    item->setCheckState(checkState);
}


void ItemsService::addDescription(QStandardItem *item, QString text)
{
    item->setWhatsThis(text);
    item->setStatusTip(text);
    item->setToolTip(text);
}

QString ItemsService::displayingStr(double data)
{
    QString visualData;
    visualData.sprintf("%06.4f", data);
    return visualData;
}

void ItemsService::makeHHeader(QStandardItem *item)
{
    makeFontBold(item);
    makeCheckable(item, true);
    alignText(item, Qt::AlignCenter);
    changeBgColor(item, Qt::lightGray);
    sizeCorrection(item);
}

void ItemsService::makeVHeader(QStandardItem *item)
{
    makeFontBold(item);
    makeCheckable(item, false);
    alignText(item, Qt::AlignRight);
    changeBgColor(item, Qt::gray);
    sizeCorrection(item);
}

void ItemsService::makeHeader(QStandardItem *item, Qt::Orientation orientation)
{
    Qt::AlignmentFlag flag;
    bool verticalOrientation = (orientation == Qt::Vertical);
    flag =  verticalOrientation ? Qt::AlignRight : Qt::AlignCenter;
    alignText(item, flag);
    item->setFlags(Qt::ItemIsUserCheckable);
    makeFontBold(item);
    makeCheckable(item, !verticalOrientation);
    changeBgColor(item, Qt::lightGray);
    if(!verticalOrientation)
        sizeCorrection(item);
}

QVector<double> ItemsService::getColVals(QStandardItemModel *m, int colNum)
{
    QVector<double> vals;
    for(int c = 0; c < m->columnCount(); c++)
    {
        if(c == colNum)
        {
            for(int r = 0; r < m->rowCount(); r++)
                vals << FloatService::fromString( m->item(r, c)->data(Qt::EditRole).toString() );
        }
    }
    return vals;
}
