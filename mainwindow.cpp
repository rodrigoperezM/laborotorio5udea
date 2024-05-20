
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , timer(new QTimer(this))
    , tiempoRestante(300) // Tiempo inicial en segundos (5 minutos)
    , puntaje(0) // Inicializar puntaje en 0
    , mira(nullptr) // Inicializar la mira como nullptr
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    connect(ui->piedra, &QPushButton::clicked, this, &MainWindow::agregarPiedra);
    connect(ui->papel, &QPushButton::clicked, this, &MainWindow::agregarPapel);
    connect(ui->tijera, &QPushButton::clicked, this, &MainWindow::agregarTijera);
    connect(ui->ingresarJugador, &QPushButton::clicked, this, &MainWindow::ingresarJugador); // Asegúrate de que el nombre coincide
    connect(ui->inicio, &QPushButton::clicked, this, &MainWindow::iniciarJuego);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarTiempo);

    timer->start(1000); // Iniciar el temporizador con intervalo de 1 segundo (1000 milisegundos)
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W: // Mover hacia arriba
            moverJugador(0, -10);
            break;
        case Qt::Key_S: // Mover hacia abajo
            moverJugador(0, 10);
            break;
        case Qt::Key_A: // Mover hacia la izquierda
            moverJugador(-10, 0);
            break;
        case Qt::Key_D: // Mover hacia la derecha
            moverJugador(10, 0);
            break;
        case Qt::Key_Space: // Tecla de ataque
            atacarObjeto();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::agregarPiedra() {
    if (scene->items().size() < 5) {
        QPixmap piedraSprite(":/Objetos/piedra.png");
        QGraphicsPixmapItem *piedraItem = new QGraphicsPixmapItem(piedraSprite);
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - piedraSprite.width());
        int posY = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : (ui->graphicsView->height() - piedraSprite.height());
        piedraItem->setPos(posX, posY);
        if (!verificarColision(piedraItem)) {
            scene->addItem(piedraItem);
            actualizarPuntaje(10);
        } else {
            delete piedraItem;
        }
    }
}

void MainWindow::agregarPapel() {
    if (scene->items().size() < 5) {
        QPixmap papelSprite(":/Objetos/papel.png");
        QGraphicsPixmapItem *papelItem = new QGraphicsPixmapItem(papelSprite);
        int posX = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : (ui->graphicsView->width() - papelSprite.width());
        int posY = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : (ui->graphicsView->height() - papelSprite.height());
        papelItem->setPos(posX, posY);
        if (!verificarColision(papelItem)) {
            scene->addItem(papelItem);
            actualizarPuntaje(20);
        } else {
            delete papelItem;
        }
    }
}

void MainWindow::agregarTijera() {
    if (scene->items().size() < 5) {
        QPixmap tijeraSprite(":/Objetos/tijera.png");
        QGraphicsPixmapItem *tijeraItem = new QGraphicsPixmapItem(tijeraSprite);
        int posX = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : (ui->graphicsView->width() - tijeraSprite.width());
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - tijeraSprite.height());
        tijeraItem->setPos(posX, posY);
        if (!verificarColision(tijeraItem)) {
            scene->addItem(tijeraItem);
            actualizarPuntaje(30);
        } else {
            delete tijeraItem;
        }
    }
}

void MainWindow::ingresarJugador() {
    if (mira == nullptr) {
        QPixmap miraSprite(":/Objetos/mira.png");
        mira = new QGraphicsPixmapItem(miraSprite);
        int posX = ui->graphicsView->width() / 2 - miraSprite.width() / 2;
        int posY = ui->graphicsView->height() / 2 - miraSprite.height() / 2;
        mira->setPos(posX, posY);
        scene->addItem(mira);
    }
    tiempoRestante = 300;
    ui->tiempoLabel->display(tiempoRestante);
    timer->start(1000);
}

void MainWindow::iniciarJuego() {
    ui->piedra->setEnabled(false);
    ui->papel->setEnabled(false);
    ui->tijera->setEnabled(false);
    tiempoRestante = 300;
    actualizarTiempo();
}

void MainWindow::actualizarTiempo() {
    tiempoRestante--;
    ui->tiempoLabel->display(tiempoRestante);
    if (tiempoRestante <= 0) {
        timer->stop();
        QMessageBox::information(this, "Fin de juego", "Se acabó el tiempo. ¡Juego terminado!");
    }
}

void MainWindow::crearObjetosAutomaticamente() {
    // Lógica para crear objetos automáticamente
}

void MainWindow::moverJugador(int dx, int dy) {
    if (mira) {
        QPointF newPos = mira->pos() + QPointF(dx, dy);
        mira->setPos(newPos);
    }
}

void MainWindow::atacarObjeto() {
    if (mira) {
        foreach (QGraphicsItem *item, scene->items()) {
            if (item != mira && item->collidesWithItem(mira)) {
                scene->removeItem(item);
                delete item;
                actualizarPuntaje(50);
                break;
            }
        }
    }
}

void MainWindow::actualizarPuntaje(int cambio) {
    puntaje += cambio;
    ui->puntajeLabel->display(puntaje);
}

void MainWindow::deshabilitarBotones() {
    ui->piedra->setEnabled(false);
    ui->papel->setEnabled(false);
    ui->tijera->setEnabled(false);
}

bool MainWindow::verificarColision(QGraphicsPixmapItem *item) {
    foreach (QGraphicsItem *otherItem, scene->items()) {
        if (item != otherItem && item->collidesWithItem(otherItem)) {
            return true;
        }
    }
    return false;
}










