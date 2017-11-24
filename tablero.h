#ifndef TABLERO_H
#define TABLERO_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QList>
#include "casilla.h"

#include <QObject>

class Tablero : public QObject
{
    Q_OBJECT
    public:
        Casilla tablero[8][8];
        bool pista;
        int negras, blancas, tableroaux[8][8];

    public:
        //Constructor
        Tablero();
        Tablero(const Tablero &t);

        //Sobrecarga operador
        Tablero& operator = (const Tablero &t);

        //Getters - Setters
        bool getPista();
        int getCasilla(int x, int y);
        int getNegras();
        int getBlancas();
        void setPista(bool value);
        void setCasilla(int x, int y, int valor);
        void setNegras(int value);
        void setBlancas(int value);

        //Métodos públicos
        void imprimir();
        bool ponerFicha(int x, int y);
        void calcularFichas(bool band = true);
        bool isJugadas();
        void reiniciar();
        void borrarFichas(int x, int y);

        //Búsquedas lineales:
        bool bDer(int x, int y, bool once = true);
        bool bIzq(int x, int y, bool once = true);
        bool bArr(int x, int y, bool once = true);
        bool bAba(int x, int y, bool once = true);
        //Búsquedas diagonales:
        bool bDAbDer(int x, int y, bool once = true);
        bool bDAbIzq(int x, int y, bool once = true);
        bool bDArDer(int x, int y, bool once = true);
        bool bDArIzq(int x, int y, bool once = true);

    public slots:
        void pistas();
};

#endif // TABLERO_H
