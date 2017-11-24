#include "juego.h"
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QFont>
#include <QDebug>
#include <windows.h>
/*
 *  David Delgado
 *  Leandro Casique
*/
Juego::Juego(QWidget *parent) : QGraphicsView(parent)
{
    //Arreglar la ventana
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(800, 600);
    //this->setBackgroundBrush(QBrush(Qt::transparent));

    //Montar la escena
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QColor(3,24,21),Qt::SolidPattern));
    this->setScene(scene);
    turno = 1;
    sigTurno = 2;
}

void Juego::pintarPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    //Pinta un panel en las coordenadas específicas con las especificaciones dadas
    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush pincel;
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(color);
    panel->setBrush(pincel);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Juego::pintarIG()
{
    //Pintar el panel de la izquierda
    this->pintarPanel(0, 0, 150, 600, Qt::black);

    //Pintar el panel central de la izquierda
    this->pintarPanel(20, this->height()/2 - 100, 120, 140, Qt::white);

    //Pintar el panel de la derecha
    this->pintarPanel(650, 0, 150, 600, Qt::white);

    //Pintar el panel central de la derecha
    this->pintarPanel(670, this->height()/2 - 100, 120, 140, Qt::black);

    //Texto de Jugador 1
    QGraphicsTextItem *p1 = new QGraphicsTextItem("Fichas del Jugador 1: ");
    p1->setPos(25, this->height()/2 - 100);
    scene->addItem(p1);

    //Ficha negra
    QGraphicsEllipseItem *f1 = new QGraphicsEllipseItem(50, 50, 40, 40);
    f1->setPos(10, this->height()/2 - 110);
    f1->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    scene->addItem(f1);

    //Texto de Jugador 2
    if(!opc){
        QGraphicsTextItem *p2 = new QGraphicsTextItem("Fichas del Jugador 2: ");
        p2->setDefaultTextColor(Qt::white);
        p2->setPos(675, this->height()/2 - 100);
        scene->addItem(p2);
    }
    else
    {
        QGraphicsTextItem *p2 = new QGraphicsTextItem("Fichas de la IA: ");
        p2->setDefaultTextColor(Qt::white);
        p2->setPos(675, this->height()/2 - 100);
        scene->addItem(p2);
    }
    //Ficha blanca
    QGraphicsEllipseItem *f2 = new QGraphicsEllipseItem(50, 50, 40, 40);
    f2->setPos(660, this->height()/2 - 110);
    f2->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    scene->addItem(f2);

    //Colocar turno de:
    this->texto = new QGraphicsTextItem();
    texto->setScale(2);                             //Arreglado profe
    this->setTurnoDe(QString("Jugador 1"));
    this->texto->setDefaultTextColor(Qt::white);
    this->texto->setPos(this->width()/2 - texto->boundingRect().width()/2 - 35, 0);
    scene->addItem(texto);
}

void Juego::menu()
{
    int xPos = this->width()/2;

    banner = new Banner();
    banner->setPos(xPos - banner->boundingRect().width()/2, 50);
    scene->addItem(banner);

    boton = new Boton * [5];
    for(int i = 0; i < 5; i++)
        boton[i] = new Boton();

    //Botón 1v1
    boton[0] = new Boton(QString("2 Jugadores"));
    boton[0]->setPos(xPos - boton[0]->boundingRect().width()/2, 200);
    connect(boton[0], SIGNAL(clicked()), this, SLOT(juego1v1()));
    scene->addItem(boton[0]);

    //Botón 1vIA
    boton[1] = new Boton(QString("1 Jugador"));
    boton[1]->setPos(xPos - boton[1]->boundingRect().width()/2, 300);
    connect(boton[1], SIGNAL(clicked()), this, SLOT(juego1vIA()));
    scene->addItem(boton[1]);

    //Botón Creditos
    boton[2] = new Boton(QString("Créditos"));
    boton[2]->setPos(xPos - boton[2]->boundingRect().width()/2, 400);
    connect(boton[2], SIGNAL(clicked()), this, SLOT(creditos()));
    scene->addItem(boton[2]);

    //Botón Salir
    boton[3] = new Boton(QString("Salir"));
    boton[3]->setPos(xPos - boton[3]->boundingRect().width()/2, 500);
    connect(boton[3], SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(boton[3]);

    //Botón Volver
    boton[4] = new Boton(QString("Volver"));
    boton[4]->setPos(xPos - boton[4]->boundingRect().width()/2, 500);
    connect(boton[4], SIGNAL(clicked()), this, SLOT(volver()));
    boton[4]->setVisible(false);
    scene->addItem(boton[4]);
}

QString Juego::getTurnoDe()
{
    return turnoDe;
}

void Juego::setTurnoDe(QString value)
{
    //Cambiamos la QString
    turnoDe = value;

    //Cambiamos el QGraphicsTextItem
    this->texto->setPlainText(QString("Turno de: ") + value);
}

void Juego::cambiarTurno()
{
    if(getTurnoDe() == QString("Jugador 1"))
        setTurnoDe(QString("Jugador 2"));
    else
        setTurnoDe(QString("Jugador 1"));
}

void Juego::fin()
{
    QString mensaje;
    bool band = false;

    if(!opc){
        if( !j1->getJugada() && !j2->getJugada() )
        {
            mensaje = "Hubo un empate, \nambos jugadores se quedaron sin jugadas";
            band = true;
        }
        else if( j1->getFichas() + j2->getFichas() == 64 )
        {
            if(j1->getFichas() > j2->getFichas())
                mensaje = "¡Jugador 1 (Negras) ha ganado!";
            else if(j1->getFichas() < j2->getFichas())
                mensaje = "¡Jugador 2 (Blancas) ha ganado!";
            else
                mensaje = "Hubo un empate";
            band = true;
        }
    }
    else
    {
        if( !j1->getJugada() && !jIA->getJugada() )
        {
            mensaje = "Hubo un empate, \nambos jugadores se quedaron sin jugadas";
            band = true;
        }
        else if( j1->getFichas() + jIA->getFichas() == 64 )
        {
            if(j1->getFichas() > jIA->getFichas())
                mensaje = "¡Jugador 1 (Negras) ha ganado!";
            else if(j1->getFichas() < jIA->getFichas())
                mensaje = "¡Jugador 2 (Blancas) ha ganado!";
            else
                mensaje = "Hubo un empate";
            band = true;
        }
    }
    if(band)
        mostrarVentanaGO(mensaje);
}

void Juego::mostrarVentanaGO(QString mensaje)
{
    //Inhabilitar todos los objetos de la escena
    for(int i = 0; i < scene->items().size(); i++)
    {
        scene->items()[i]->setEnabled(false);
    }
    if(opc)
        win = true;

    //Mostrar panel semi-transparente
    this->pintarPanel(0, 0, 800, 600, Qt::black, 0.65);

    //Mostrar panel de fin de juego
    this->pintarPanel(250, 150, 300, 340, Qt::lightGray, 0.75);

    //Crear botón de jugar de nuevo
    Boton *again = new Boton(QString("Jugar de nuevo"));
    again->setPos(this->width()/2 - again->boundingRect().width()/2, 250);
    connect(again, SIGNAL(clicked()), this, SLOT(reiniciar()));
    scene->addItem(again);

    //Crear botón de menú
    Boton *bmenu = new Boton(QString("Menú"));
    bmenu->setPos(this->width()/2 - bmenu->boundingRect().width()/2, 325);
    connect(bmenu, SIGNAL(clicked()), this, SLOT(backToMenu()));
    scene->addItem(bmenu);

    //Crear botón de salir
    Boton *salir = new Boton(QString("Salir"));
    salir->setPos(this->width()/2 - salir->boundingRect().width()/2, 400);
    connect(salir, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(salir);

    //Crear texto anunciando el ganador
    QGraphicsTextItem *ganador = new QGraphicsTextItem(mensaje);
    ganador->setFont(QFont("comic sans", 12));
    ganador->setPos(this->width()/2 - ganador->boundingRect().width()/2, 200);
    scene->addItem(ganador);
}

void Juego::juego1v1()
{
    opc = false;
    //Limpio el menu
    scene->clear();

    //Instancio el tablero
    tablero = new Tablero();
    tablero->imprimir();

    //Intancio el boton pistas
    Boton *pista = new Boton(QString("Pista"));
    pista->setPos(this->width()/2 - pista->boundingRect().width() - 5, 540);
    connect(pista, SIGNAL(clicked()), tablero, SLOT(pistas()));
    scene->addItem(pista);

    //Instancio un botón de pausa
    Boton *pausa = new Boton(QString("Menú"));
    pausa->setPos(this->width()/2 + 5, 540);
    connect(pausa, SIGNAL(clicked()), this, SLOT(backToMenu()));
    scene->addItem(pausa);

    //Pinto la interfaz del juego
    this->pintarIG();

    //Instancio los objetos de Jugador
    j1 = new Jugador(turno);
    j1->setPos(70, this->height()/2 - 10);
    j2 = new Jugador(sigTurno);
    j2->setPos(720, this->height()/2 - 10);
    j2->setDefaultTextColor(Qt::white);
    scene->addItem(j1);
    scene->addItem(j2);
}

void Juego::juego1vIA()
{
    opc = true;
    win = false;
    //Limpio el menu
    scene->clear();

    //Instancio el tablero
    tablero = new Tablero();
    tablero->imprimir();

    //Intancio el boton pistas
    Boton *pista = new Boton(QString("Pista"));
    pista->setPos(this->width()/2 - pista->boundingRect().width() - 5, 540);
    connect(pista, SIGNAL(clicked()), tablero, SLOT(pistas()));
    scene->addItem(pista);

    //Instancio un botón de pausa
    Boton *pausa = new Boton(QString("Menú"));
    pausa->setPos(this->width()/2 + 5, 540);
    connect(pausa, SIGNAL(clicked()), this, SLOT(backToMenu()));
    scene->addItem(pausa);

    //Pinto la interfaz del juego
    this->pintarIG();

    //Instancio los objetos de Jugador
    j1 = new Jugador(turno);
    j1->setPos(68, this->height()/2 - 10);
    jIA = new IA(sigTurno);
    jIA->setPos(720, this->height()/2 - 10);
    jIA->setDefaultTextColor(Qt::white);
    scene->addItem(j1);
    scene->addItem(jIA);
}

void Juego::reiniciar()
{
    //Limpiar todo y volver a llamar algún juego
    this->turno = 1;
    this->sigTurno = 2;
    delete tablero;
    if(!opc)
        juego1v1();
    else
        juego1vIA();
}

void Juego::backToMenu()
{
    //Limpiar todo y volver al menu
    this->turno = 1;
    this->sigTurno = 2;
    delete tablero;
    scene->clear();
    menu();
}

void Juego::creditos()
{
    creopc = true;
    for(int i = 0; i < 4; i++)
        boton[i]->setVisible(false);
    boton[4]->setVisible(true);

    //Crear el título
    titulo = new QGraphicsTextItem("Programado por:\n"
                                   "David Delgado\n"
                                   "Leandro Casique");
    titulo->setFont(QFont("Cursive", 30));
    titulo->setDefaultTextColor(Qt::white);
    int xPos = this->width()/2 - titulo->boundingRect().width()/2;
    titulo->setPos(xPos, 300);
    this->scene->addItem(titulo);
}

void Juego::volver()
{
    for(int i = 0 ; i < 4; i++)
        boton[i]->setVisible(true);
    boton[4]->setVisible(false);

    if( creopc )
    {
        scene->removeItem(titulo);
        delete titulo;
    }
}
