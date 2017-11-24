#ifndef CASILLA_H
#define CASILLA_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <ficha.h>

class Casilla : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    private:
        int valor, x, y;
        Ficha *ficha;

    public:
        //Constructor
        Casilla(QGraphicsItem *parent = 0);

        //Sobrecarga operadores
        Casilla& operator = (const Casilla &c);

        //Getters y Setters
        int getValor();
        int getX() const;
        int getY() const;
        Ficha *getFicha();
        void setValor(int value);
        void setPosicion(int x, int y);
        void setCoordenadas(int x, int y);
        void setColor();

        //Métodos públicos


        //Eventos
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CASILLA_H
