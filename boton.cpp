#include "boton.h"
#include <QGraphicsTextItem>
#include <QBrush>

#include <QDebug>
/*
 *  David Delgado
 *  Leandro Casique
*/
Boton::Boton(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //Dibujar el boton
    this->setRect(0, 0, 200, 50);
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(Qt::darkCyan);
    this->setBrush(pincel);

    this->setAcceptHoverEvents(true);
}

Boton::Boton(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //Dibujar el boton
    this->setRect(0, 0, 200, 50);
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(Qt::darkCyan);
    this->setBrush(pincel);

    //Escribir el texto
    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    //Permitir responder a los hover events
    this->setAcceptHoverEvents(true);
}

void Boton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Boton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //Cambiar el color a Cyan
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(Qt::cyan);
    setBrush(pincel);
}

void Boton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //Cambiar el color a darkCyan
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(Qt::darkCyan);
    setBrush(pincel);
}

