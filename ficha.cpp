#include "ficha.h"
#include <QBrush>
#include <iostream>
/*
 *  David Delgado
 *  Leandro Casique
*/
Ficha::Ficha(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    //Dibujar la ficha
    this->setRect(50, 50, 40, 40);
}

Ficha::Ficha(int color, QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    //Dibujar la ficha
    this->setRect(50, 50, 40, 40);

    //Colorear la ficha
    QBrush pincel;

    pincel.setStyle(Qt::SolidPattern);

    if(color == 1)
        pincel.setColor(Qt::black);
    else if(color == 2)
        pincel.setColor(Qt::white);
    else if(color == -1)
        pincel.setColor(Qt::darkGray);

    this->setBrush(pincel);
}

Ficha::~Ficha()
{
    this->setVisible(false);
}


void Ficha::setColor(int color)
{
    //Colorear la ficha
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    if(color == 1)
        pincel.setColor(Qt::black);
    else
        pincel.setColor(Qt::white);

    this->setBrush(pincel);
}
