/*#include "ObjetoJuego.h"
#include <QGraphicsScene>

ObjetoJuego::ObjetoJuego(QGraphicsItem *parent) : QGraphicsItem(parent) {}

ObjetoJuego::~ObjetoJuego() {}

void ObjetoJuego::advance(int step) {}

Tijeras::Tijeras(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Tijeras::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setX(newPos.x() + 1); // Velocidad de movimiento horizontal de las tijeras

    if (newPos.x() > scene()->width()) {
        newPos.setX(0); // Si llega al borde derecho, vuelve al borde izquierdo
    }

    setPos(newPos);
}

Piedra::Piedra(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Piedra::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setY(newPos.y() + 1); // Velocidad de movimiento vertical de la piedra

    if (newPos.y() > scene()->height()) {
        newPos.setY(0); // Si llega al borde inferior, vuelve al borde superior
    }

    setPos(newPos);
}

Papel::Papel(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Papel::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setX(newPos.x() + 1); // Velocidad de movimiento horizontal del papel
    newPos.setY(newPos.y() + 1); // Velocidad de movimiento vertical del papel

    QRectF sceneRect = scene()->sceneRect();

    // Rebote en las paredes
    if (newPos.x() < sceneRect.left() || newPos.x() > sceneRect.right()) {
        newPos.setX(qBound(sceneRect.left(), newPos.x(), sceneRect.right()));
    }
    if (newPos.y() < sceneRect.top() || newPos.y() > sceneRect.bottom()) {
        newPos.setY(qBound(sceneRect.top(), newPos.y(), sceneRect.bottom()));
    }

    setPos(newPos);
}*/
// En el archivo ObjetoJuego.cpp

/*#include "ObjetoJuego.h"
#include <QGraphicsScene>

ObjetoJuego::ObjetoJuego(QGraphicsItem *parent) : QGraphicsItem(parent) {}

ObjetoJuego::~ObjetoJuego() {}

void ObjetoJuego::advance(int step) {}


Tijeras::Tijeras(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Tijeras::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setX(newPos.x() + 1); // Mover las tijeras hacia la derecha

    if (newPos.x() > scene()->width()) {
        newPos.setX(0); // Si llega al borde derecho, vuelve al borde izquierdo
    }

    setPos(newPos);
}

Piedra::Piedra(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Piedra::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setY(newPos.y() + 1); // Mover la piedra hacia abajo

    if (newPos.y() > scene()->height()) {
        newPos.setY(0); // Si llega al borde inferior, vuelve al borde superior
    }

    setPos(newPos);
}

Papel::Papel(QGraphicsItem *parent) : ObjetoJuego(parent) {}

void Papel::advance(int step) {
    if (!step) return;

    QPointF newPos = pos();
    newPos.setX(newPos.x() + 1); // Mover el papel hacia la derecha
    newPos.setY(newPos.y() + 1); // Mover el papel hacia abajo

    QRectF sceneRect = scene()->sceneRect();

    // Rebote en las paredes
    if (newPos.x() < sceneRect.left() || newPos.x() > sceneRect.right()) {
        newPos.setX(qBound(sceneRect.left(), newPos.x(), sceneRect.right()));
    }
    if (newPos.y() < sceneRect.top() || newPos.y() > sceneRect.bottom()) {
        newPos.setY(qBound(sceneRect.top(), newPos.y(), sceneRect.bottom()));
    }

    setPos(newPos);
}*/

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

    // Implementa aquí la lógica de movimiento común para todos los objetos
}

Tijeras::Tijeras(QGraphicsItem *parent) : ObjetoJuego(parent)
{
}

void Tijeras::advance(int step)
{
    if (!step) {
        return;
    }

    // Implementa aquí la lógica de movimiento específica para las tijeras
    setPos(pos().x() + 1, pos().y()); // Movimiento hacia la derecha
}

Piedra::Piedra(QGraphicsItem *parent) : ObjetoJuego(parent)
{
}

void Piedra::advance(int step)
{
    if (!step) {
        return;
    }

    // Implementa aquí la lógica de movimiento específica para las piedras
    setPos(pos().x(), pos().y() + 1); // Movimiento hacia abajo
    setPos(pos().x()+1, pos().y());
}

Papel::Papel(QGraphicsItem *parent) : ObjetoJuego(parent)
{
}

void Papel::advance(int step)
{
    if (!step) {
        return;
    }

    // Implementa aquí la lógica de movimiento específica para los papeles
    // Movimiento en diagonal hacia la esquina superior izquierda
    setPos(pos().x() - 1, pos().y() - 1);
}


