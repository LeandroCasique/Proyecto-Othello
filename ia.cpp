#include "ia.h"
#include "juego.h"
/*
 *  David Delgado
 *  Leandro Casique
*/
extern Juego *othello;

IA::IA(int turno) : Jugador(turno)
{

}

Tablero IA::getRaiz() const
{
    return this->raiz;
}

void IA::setRaiz(Tablero *value)
{
    raiz = (*value);
}

int IA::getCasilla(int i, int j){
    return this->resp.getCasilla(i,j);
}

int IA::getX() const
{
    return x;
}

int IA::getY() const
{
    return y;
}

int IA::getCanBlancas()
{
    return resp.getBlancas();
}

int IA::getCanNegras()
{
    return resp.getNegras();
}

void IA::minimax()
{
    raiz.setPista(false);

    tablaux = raiz;
    int aux, v = INT_MIN;
    int n = othello->j1->getFichas();
    int b = this->getFichas();
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(tablaux.ponerFicha(i, j)) {
                aux = this->getMIN();

                if(aux > v) {
                    v = aux;
                    x = i; y = j;
                    resp = tablaux;
                    resp.setNegras(othello->j1->getFichas());
                    resp.setBlancas(this->getFichas());
                }
                tablaux = raiz;
                othello->j1->setFichas(n);
                setFichas(b);
            }
}

int IA::getMIN()
{
    t = tablaux;

    int v = INT_MAX, aux;
    othello->turno = 1;
    othello->sigTurno = 2;
    int n = othello->j1->getFichas();
    int b = this->getFichas();

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if( t.ponerFicha(i, j) )
            {
                aux = this->getMAX();

                if(aux < v)
                    v = aux;
                t = tablaux;
                othello->j1->setFichas(n);
                this->setFichas(b);
            }
    othello->turno = 2;
    othello->sigTurno = 1;
    return v;
}

int IA::getMAX()
{
    return this->getFichas() - othello->j1->getFichas();
}
