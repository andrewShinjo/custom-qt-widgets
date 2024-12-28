#ifndef MBIMAGE_H
#define MBIMAGE_H

#include <QObject>

class MbImage : public QObject
{
    Q_OBJECT
public:
    explicit MbImage(QObject *parent = nullptr);

signals:
};

#endif // MBIMAGE_H
