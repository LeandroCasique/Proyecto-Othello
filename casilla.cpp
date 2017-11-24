#include "casilla.h"
#include "juego.h"
#include <QBrush>
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <windows.h>
#include <QDebug>

extern Juego *othello;

Casilla::Casilla(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //Dibujar la casilla
    this->setRect(50, 50, 50, 50);

    //Colorear la casilla
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(Qt::darkCyan);
    this->setBrush(pincel);

    //Casilla vacía
    valor = 0;
    ficha = NULL;
}

Casilla& Casilla:: operator = (const Casilla &c)
{
    valor = c.valor;
    x = c.x;
    y = c.y;
    ficha = c.ficha;

    return *this;
}

int Casilla::getValor()
{
    return valor;
}

int Casilla::getX() const
{
    return x;
}

int Casilla::getY() const
{
    return y;
}

Ficha *Casilla::getFicha()
{
    return ficha;
}

void Casilla::setValor(int value)
{
    valor = value;

    if(valor == -1 || valor == 0){
        this->setColor();
        return;
    }

    if(valor != 0 && !ficha)
        ficha = new Ficha(valor);
    else if(valor != 0 && ficha)
        ficha->setColor(valor);
}

void Casilla::setPosicion(int x, int y)
{
    this->setPos(x, y);
    if(ficha)
        ficha->setPos(x+5, y+5);
}

void Casilla::setCoordenadas(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Casilla::setColor()
{
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    if(valor == -1)
        pincel.setColor(Qt::cyan);
    else
        pincel.setColor(Qt::darkCyan);

    this->setBrush(pincel);
}

void Casilla::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(valor == -1)
    {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                if(othello->tablero->getCasilla(i, j) == -1)
                    othello->tablero->setCasilla(i, j, 0);
        othello->tablero->setPista(false);
    }

    //Si presiono en una casilla, colocaré una ficha
    if(valor == 0 && othello->tablero->ponerFicha(this->x, this->y))
    {
        this->setValor(othello->turno);
        if(!othello->opc)
        {
            if(othello->turno == othello->j1->getTurno())
            {
                othello->turno++;
                othello->sigTurno--;
                if(othello->tablero->isJugadas())
                {
                    othello->j2->setJugada(true);
                    othello->cambiarTurno();
                }
                else
                {
                    othello->j2->setJugada(false);
                    othello->turno--;
                    othello->sigTurno++;
                }
            }
            else if(othello->turno == othello->j2->getTurno() )
            {
                othello->turno--;
                othello->sigTurno++;
                if(othello->tablero->isJugadas())
                {
                    othello->j1->setJugada(true);
                    othello->cambiarTurno();
                }
                else
                {
                    othello->j1->setJugada(false);
                    othello->turno++;
                    othello->sigTurno--;
                }
            }
        }
        else
        {
            if(othello->turno == othello->j1->getTurno())
            {
                othello->turno = 2;
                othello->sigTurno = 1;
                othello->tablero->imprimir();
                othello->fin();
                if(!othello->win)
                if(othello->tablero->isJugadas())
                {
                    othello->jIA->setJugada(true);
                    othello->jIA->setRaiz(othello->tablero);
                    othello->jIA->minimax();

                    for(int i = 0; i < 8; i++)
                        for(int j = 0; j < 8; j++)
                            othello->tablero->setCasilla(i, j, othello->jIA->getCasilla(i, j));

                    othello->j1->setFichas(othello->jIA->getCanNegras());
                    othello->jIA->setFichas(othello->jIA->getCanBlancas());
                    othello->turno--;
                    othello->sigTurno++;
                    othello->cambiarTurno();

                    if(!othello->tablero->isJugadas())
                        othello->j1->setJugada(false);
                }
                else
                {
                    othello->jIA->setJugada(false);
                    othello->turno--;
                    othello->sigTurno++;
                }
            }
        }
        if(!othello->win)
        {
            othello->tablero->imprimir();
            othello->fin();
        }
    }
}
