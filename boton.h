#ifndef BOTON_H
#define BOTON_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Boton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    private:
        QGraphicsTextItem *text;

    public:
        //Constructor
        Boton(QGraphicsItem *parent = 0);
        Boton(QString name, QGraphicsItem * parent = 0);

        //Métodos setter y getter
        void setTexto(QGraphicsTextItem *text);

        //Métodos públicos (eventos)
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    signals:
        void clicked();
};

#endif // BOTON_H
