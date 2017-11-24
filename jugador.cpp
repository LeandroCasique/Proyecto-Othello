#include <jugador.h>

#include <QFont>
/*
 *  David Delgado
 *  Leandro Casique
*/
Jugador::Jugador(int turno, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    fichas = 2;
    jugada = true;
    this->turno = turno;

    //Escribir el texto
    this->setPlainText(QString(QString::number(fichas)));
    this->setFont(QFont("Comic Sans", 16));
}

void Jugador::actualizarTexto()
{
    this->setPlainText(QString(QString::number(fichas)));
}

void Jugador::reiniciar()
{
    fichas = 2;
    jugada = true;
    this->setPlainText(QString(QString::number(fichas)));
}

int Jugador::getFichas()
{
    return fichas;
}

void Jugador::setFichas(int value)
{
    fichas = value;
    this->actualizarTexto();
}

int Jugador::getTurno()
{
    return turno;
}

void Jugador::setTurno(int value)
{
    turno = value;
}

bool Jugador::getJugada()
{
    return jugada;
}

void Jugador::setJugada(bool value)
{
    jugada = value;
}
