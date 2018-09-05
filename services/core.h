#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QImage>
#include "single_area.h"
#include <QVector>
#include <QImage>
#include <QStack>
#include <QPoint>

class Core : public QObject
{
    Q_OBJECT
    public:
        Core(const QImage& img): bin(img), filePath(QString()) {}
        Core(): bin(QImage()), filePath(QString()) {}

        using Labels = QVector<QVector<quint64>>;
        using Labels_row = QVector<quint64>;
        using Objects = QVector<S_area>;

        static Objects objects;
        static Labels labels;



        void setBin(const QImage &value);

public slots:
        void select();
    signals:
        void SelectingFinished();
        void dataIsSaved();
    private:
        QImage bin;
        QString filePath;
};

#endif // WORKER_H
