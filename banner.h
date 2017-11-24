#ifndef BANNER_H
#define BANNER_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Banner : public QGraphicsPixmapItem
{
    public:
        Banner(QGraphicsItem *parent = 0);
};

#endif // BANNER_H
