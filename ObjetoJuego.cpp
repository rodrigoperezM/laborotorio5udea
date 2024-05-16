
// ObjetoJuego.cpp
#include "ObjetoJuego.h"
#include <QGraphicsScene>

ObjetoJuego::ObjetoJuego(QGraphicsItem *parent) : QGraphicsItem(parent)
{
}

ObjetoJuego::~ObjetoJuego()
{
}

void ObjetoJuego::advance(int step)
{
    if (!step) {
        return;
    }

    // Implementación de la lógica de movimiento común para todos los objetos
}

Tijeras::Tijeras(QGraphicsItem *parent) : ObjetoJuego(parent)
{
}

void Tijeras::advance(int step)
{
    if (!step) {
        return;
    }

    // Mover las tijeras de izquierda a derecha
    setPos(pos().x() + 1, pos().y());

    // Si las tijeras salen de la escena por la derecha, eliminarlas
    if (pos().x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
    }
}
void Piedra::advance(int step)
{
    if (!step) {
        return;
    }

    // Mover la piedra de arriba hacia abajo
    setPos(pos().x(), pos().y() + 1);

    // Si la piedra sale de la escena por abajo, eliminarla
    if (pos().y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}

void Papel::advance(int step)
{
    if (!step) {
        return;
    }

    // Mover el papel en diagonal hacia la esquina inferior derecha
    setPos(pos().x() + 1, pos().y() + 1);

    // Si el papel sale de la escena por abajo o por la derecha, eliminarlo
    if (pos().x() > scene()->width() || pos().y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
