/*#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Explosion(QGraphicsItem *parent = nullptr);
    void startExplosion(const QPointF &position);

private slots:
    void hideExplosion();

private:
    QTimer *timer;
};

#endif // EXPLOSION_H*/

/*#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Explosion(QGraphicsItem *parent = nullptr);
    void startExplosion(const QPointF &position);

private slots:
    void hideExplosion();

private:
    QTimer *timer;
};

#endif // EXPLOSION_H*/

/*#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Explosion(QGraphicsItem *parent = nullptr);
    void startExplosion(const QPointF &position);

private slots:
    void hideExplosion();

private:
    QTimer *timer;
};

#endif // EXPLOSION_H*/

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Explosion(QGraphicsItem *parent = nullptr);
    ~Explosion();
    void startExplosion(const QPointF &position);

private slots:
    void hideExplosion();

private:
    QTimer *timer;
};

#endif // EXPLOSION_H



