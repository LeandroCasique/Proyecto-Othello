#include "banner.h"
/*
 *  David Delgado
 *  Leandro Casique
*/
Banner::Banner(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/imagenes/othello.png"));
}
