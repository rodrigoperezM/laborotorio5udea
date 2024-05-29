/*#include "explosion.h"

Explosion::Explosion(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
    // Cargar la imagen de la explosión
    setPixmap(QPixmap(":/Objetos/explosion.png"));
    setVisible(false); // Ocultar por defecto

    // Configurar el temporizador para ocultar la explosión después de un tiempo
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Explosion::hideExplosion);
}

void Explosion::startExplosion(const QPointF &position)
{
    setPos(position);
    setVisible(true);
    if (!timer->isActive()) {
        timer->start(500); // Ocultar la explosión después de 500 ms (ajusta según sea necesario)
    }
}

void Explosion::hideExplosion()
{
    setVisible(false);
    timer->stop();
}*/

/*#include "explosion.h"

Explosion::Explosion(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this))
{
    setPixmap(QPixmap(":/Objetos/explosion.png"));
    setVisible(false);

    connect(timer, &QTimer::timeout, this, &Explosion::hideExplosion);
}

void Explosion::startExplosion(const QPointF &position)
{
    setPos(position);
    setVisible(true);
    if (!timer->isActive()) {
        timer->start(500); // Ocultar la explosión después de 500 ms
    }
}

void Explosion::hideExplosion()
{
    setVisible(false);
    timer->stop();
}*/

/*#include "explosion.h"

Explosion::Explosion(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this))
{
    setPixmap(QPixmap(":/Objetos/explosion.png"));
    setVisible(false);

    connect(timer, &QTimer::timeout, this, &Explosion::hideExplosion);
}

void Explosion::startExplosion(const QPointF &position)
{
    setPos(position);
    setVisible(true);
    timer->start(500); // Ocultar la explosión después de 500 ms
}

void Explosion::hideExplosion()
{
    setVisible(false);
    timer->stop();
}*/

#include "explosion.h"

Explosion::Explosion(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this))
{
    setPixmap(QPixmap(":/Objetos/explosion.png"));
    setVisible(false);

    connect(timer, &QTimer::timeout, this, &Explosion::hideExplosion);
}

Explosion::~Explosion() // Definir el destructor
{
    delete timer;
}

void Explosion::startExplosion(const QPointF &position)
{
    setPos(position);
    setVisible(true);
    timer->start(500); // Ocultar la explosión después de 500 ms
}

void Explosion::hideExplosion()
{
    setVisible(false);
    timer->stop();
}



