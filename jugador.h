#ifndef JUGADOR_H
#define JUGADOR_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsTextItem>

class Jugador : public QGraphicsTextItem
{
    private:
        int fichas;
        int turno;
        bool jugada;

    public:
        //Constructores
        Jugador(int turno, QGraphicsItem *parent = 0);

        //Métodos públicos:
        void actualizarTexto();
        void reiniciar();

        //Métodos getter y setter
        int getFichas();
        void setFichas(int value);
        int getTurno();
        void setTurno(int value);
        bool getJugada();
        void setJugada(bool value);
};

#endif // JUGADOR_H
