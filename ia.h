#ifndef IA_H
#define IA_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include "tablero.h"
#include "jugador.h"

class IA : public Jugador
{
    Tablero raiz, tablaux, t, resp;
    int x, y;

    public:
        //Constructor
        IA(int turno);

        //Getter y setters
        Tablero getRaiz() const;
        void setRaiz(Tablero *value);
        int getCasilla(int i, int j);
        int getX() const;
        int getY() const;
        int getCanBlancas();
        int getCanNegras();

        //Métodos Minimax
        void minimax();
        int getMIN();
        int getMAX();
};

#endif // IA_H
