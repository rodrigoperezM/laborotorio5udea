
// ObjetoJuego.h
#ifndef OBJETOJUEGO_H
#define OBJETOJUEGO_H

#include <QGraphicsItem>

class ObjetoJuego : public QGraphicsItem
{
public:
    explicit ObjetoJuego(QGraphicsItem *parent = nullptr);
    ~ObjetoJuego() override;

protected:
    void advance(int step) override;
};

class Tijeras : public ObjetoJuego
{
public:
    explicit Tijeras(QGraphicsItem *parent = nullptr);

protected:
    void advance(int step) override;
};

class Piedra : public ObjetoJuego
{
public:
    explicit Piedra(QGraphicsItem *parent = nullptr);

protected:
    void advance(int step) override;
};

class Papel : public ObjetoJuego
{
public:
    explicit Papel(QGraphicsItem *parent = nullptr);

protected:
    void advance(int step) override;
};

#endif // OBJETOJUEGO_H
