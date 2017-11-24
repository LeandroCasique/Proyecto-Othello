#include "tablero.h"
#include "juego.h"
#include <QRectF>

#include <QDebug>
/*
 *  David Delgado
 *  Leandro Casique
*/
extern Juego *othello;

Tablero::Tablero()
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            tablero[i][j].setCoordenadas(i, j);

    tablero[3][3].setValor(2);
    tablero[3][4].setValor(1);
    tablero[4][3].setValor(1);
    tablero[4][4].setValor(2);					//Inicio el tablero original
    pista = false;                              //Inicio la pista en false
}

Tablero::Tablero(const Tablero &t)
{

}

Tablero &Tablero::operator = (const Tablero &t)
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            tablero[i][j] = t.tablero[i][j];
        }

    pista = t.pista;
    blancas = t.blancas;
    negras = t.negras;
    return *this;
}

bool Tablero::getPista()
{
    return pista;
}

int Tablero::getCasilla(int x, int y)
{
    return tablero[x][y].getValor();
}

int Tablero::getNegras()
{
    return negras;
}

int Tablero::getBlancas()
{
    return blancas;
}

void Tablero::setPista(bool value)
{
    pista = value;
}

void Tablero::setCasilla(int x, int y, int valor)
{
    tablero[x][y].setValor(valor);
}

void Tablero::setNegras(int value)
{
    negras = value;
}

void Tablero::setBlancas(int value)
{
    blancas = value;
}

void Tablero::imprimir()
{
    int y = 50;
    for(int i = 0; i < 8; i++)
    {
        int x  = 150;
        for(int j = 0; j < 8; j++)
        {
            tablero[i][j].setPosicion(x + 1, y + 51 * i);

            othello->scene->addItem(&tablero[i][j]);

            if(tablero[i][j].getValor() == 1)
                othello->scene->addItem(tablero[i][j].getFicha());
            else if(tablero[i][j].getValor() == 2)
                othello->scene->addItem(tablero[i][j].getFicha());

            x+=50;
        }
    }
}

bool Tablero::ponerFicha(int x, int y)
{
    bool band = false;

    //if(tablero[x][y+1].getValor() == othello->sigTurno)
    if( bDer(x, y) )			//Si el llamado al método de búsqueda por derecha es true
        band = true;												//band = true

    //if(tablero[x][y-1].getValor() == othello->sigTurno)
    if( bIzq(x, y) )			//Si el llamado al método de búsqueda por izquierda es true
        band = true;

    //if(tablero[x-1][y].getValor() == othello->sigTurno)
    if( bArr(x, y) )			//Si el llamado al método de búsqueda por arriba es true
        band = true;

    //if(tablero[x+1][y].getValor() == othello->sigTurno)
    if( bAba(x, y) )			//Si el llamado al método de búsqueda por abajo es true
        band = true;

    //if(tablero[x+1][y+1].getValor() == othello->sigTurno)
    if( bDAbDer(x, y) )         //Si el llamado al método de búsqueda por la diagonal abajo-derecha es true
        band = true;

    //if(tablero[x+1][y-1].getValor() == othello->sigTurno)
    if( bDAbIzq(x, y) )         //Si el llamado al método de búsqueda por la diagonal abajo-izquierda es true
        band = true;

    //if(tablero[x-1][y+1].getValor() == othello->sigTurno)
    if( bDArDer(x, y) )         //Si el llamado al método de búsqueda por la diagonal arriba-derecha es true
        band = true;

    //if(tablero[x-1][y-1].getValor() == othello->sigTurno)
    if( bDArIzq(x, y) )         //Si el llamado al método de búsqueda por la diagonal arriba-izquierda es true
        band = true;

    return band;
}

void Tablero::calcularFichas(bool band)
{
    if(!othello->opc){
        if( othello->turno == othello->j1->getTurno() )
        {
            othello->j1->setFichas(othello->j1->getFichas()+1);
            if(band)
                othello->j2->setFichas(othello->j2->getFichas()-1);
        }
        else
        {
            othello->j2->setFichas(othello->j2->getFichas()+1);
            if(band)
                othello->j1->setFichas(othello->j1->getFichas()-1);
        }
    }
    else
    {
        if( othello->turno == othello->j1->getTurno() )
        {
            othello->j1->setFichas(othello->j1->getFichas()+1);
            if(band)
                othello->jIA->setFichas(othello->jIA->getFichas()-1);
        }
        else
        {
            othello->jIA->setFichas(othello->jIA->getFichas()+1);
            if(band)
                othello->j1->setFichas(othello->j1->getFichas()-1);
        }
    }
}

bool Tablero::isJugadas()
{
    this->pista = true;

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            if( (tablero[i][j].getValor() == 0 || tablero[i][j].getValor() == -1) && this->ponerFicha(i, j))
            {
                this->pista = false;
                return true;
            }
        }
    this->pista = false;
    return false;
}

void Tablero::reiniciar()
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            this->borrarFichas(i, j);
        }

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            tablero[i][j].setValor(0);
        }

    tablero[3][3].setValor(2);
    tablero[3][4].setValor(1);
    tablero[4][3].setValor(1);
    tablero[4][4].setValor(2);					//Inicio el tablero original
    pista = false;
}

void Tablero::borrarFichas(int x, int y)
{
    tablero[x][y].getFicha()->~Ficha();
}

bool Tablero::bDer(int x, int y, bool once)
{
    bool band = false;

    if(y < 7){
        if(tablero[x][y+1].getValor() == othello->sigTurno)
            band = this->bDer(x, y+1, false);
        else if(tablero[x][y+1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bIzq(int x, int y, bool once)
{
    bool band = false;

    if(y > 0){
        if(tablero[x][y-1].getValor() == othello->sigTurno)
            band = this->bIzq(x, y-1, false);
        else if(tablero[x][y-1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bArr(int x, int y, bool once)
{
    bool band = false;

    if(x > 0){
        if(tablero[x-1][y].getValor() == othello->sigTurno)
            band = this->bArr(x-1, y, false);
        else if(tablero[x-1][y].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bAba(int x, int y, bool once)
{
    bool band = false;

    if(x < 7){
        if(tablero[x+1][y].getValor() == othello->sigTurno)
            band = this->bAba(x+1, y, false);
        else if(tablero[x+1][y].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bDAbDer(int x, int y, bool once)
{
    bool band = false;

    if(x < 7 && y < 7){
        if(tablero[x+1][y+1].getValor() == othello->sigTurno)
            band = this->bDAbDer(x+1, y+1, false);
        else if(tablero[x+1][y+1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bDAbIzq(int x, int y, bool once)
{
    bool band = false;

    if(x < 7 && y > 0){
        if(tablero[x+1][y-1].getValor() == othello->sigTurno)
            band = this->bDAbIzq(x+1, y-1, false);
        else if(tablero[x+1][y-1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bDArDer(int x, int y, bool once)
{
    bool band = false;

    if(x > 0 && y < 7){
        if(tablero[x-1][y+1].getValor() == othello->sigTurno)
            band = this->bDArDer(x-1, y+1, false);
        else if(tablero[x-1][y+1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}

bool Tablero::bDArIzq(int x, int y, bool once)
{
    bool band = false;

    if(x > 0 && y > 0){
        if(tablero[x-1][y-1].getValor() == othello->sigTurno)
            band = this->bDArIzq(x-1, y-1, false);
        else if(tablero[x-1][y-1].getValor() == othello->turno)
        {
            if(!once)
            {
                if(!pista){
                    tablero[x][y].setValor(othello->turno);
                    this->calcularFichas();
                }
                return true;
            }
            return false;
        }
        else
            return false;
    }

    if(band)
    {
        if(!pista){
            if( tablero[x][y].getValor() == othello->sigTurno )
                this->calcularFichas();
            if( tablero[x][y].getValor() == 0 )
                this->calcularFichas(false);
            tablero[x][y].setValor(othello->turno);
        }
        return band;
    }
    return false;
}



void Tablero::pistas()
{
    pista = true;

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            if(pista && tablero[i][j].getValor() == 0 && this->ponerFicha(i, j))
                tablero[i][j].setValor(-1);
        }

    this->imprimir();
}
