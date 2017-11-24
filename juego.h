#ifndef JUEGO_H
#define JUEGO_H
/*
 *  David Delgado
 *  Leandro Casique
*/
#include <QGraphicsView>
#include "tablero.h"
#include "banner.h"
#include "boton.h"
#include "jugador.h"
#include "ia.h"

class Juego : public QGraphicsView  //QGraphicsView ya hereda de QObject por lo que no es necesario agregar la herencia de QObject
{
    Q_OBJECT
    private:
        //Atributos privados
        QString turnoDe;
        QGraphicsTextItem *texto, *titulo;
        Banner *banner;
        Boton **boton;

        //Métodos privados
        void pintarPanel(int x, int y, int width, int height, QColor color, double opacity = 1);
        void pintarIG();

    public:
        //Constructor:
        Juego(QWidget *parent = 0);

        //Atributos Públicos:
        QGraphicsScene *scene;
        Tablero *tablero;
        Jugador *j1, *j2;
        IA *jIA;
        int turno, sigTurno;
        bool opc, win, creopc;

        //Métodos públicos:
        void menu();
        QString getTurnoDe();
        void setTurnoDe(QString value);
        void cambiarTurno();
        void fin();
        void mostrarVentanaGO(QString mensaje);

    public slots:
        void juego1v1();
        void juego1vIA();
        void reiniciar();
        void backToMenu();
        void creditos();
        void volver();
};

#endif // JUEGO_H
