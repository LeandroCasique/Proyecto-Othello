#ifndef FICHA_H
#define FICHA_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsEllipseItem>
#include <QString>

class Ficha : public QGraphicsEllipseItem
{
    private:
        //QString duenio;

    public:
        //Constructores
        Ficha(QGraphicsItem *parent = 0);
        Ficha(int color, QGraphicsItem *parent = 0);
        ~Ficha();

        //Métodos públicos
        void setColor(int color);
};

#endif // FICHA_H
