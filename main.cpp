#include <QApplication>
#include "juego.h"

//#define tam 8;
/*
 *  David Delgado
 *  Leandro Casique
*/
Juego *othello;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    othello = new Juego();
    othello->show();
    othello->menu();

    return a.exec();
}
