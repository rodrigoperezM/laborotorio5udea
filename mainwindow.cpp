
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , timer(new QTimer(this))
    , autoCreateTimer(new QTimer(this)) // Inicializar autoCreateTimer
    , tiempoRestante(300) // Tiempo inicial en segundos (5 minutos)
    , puntaje(0) // Inicializar puntaje en 0
    , puntajeTijeras(0) // Inicializar puntaje tijeras en 0
    , puntajePiedra(0) // Inicializar puntaje piedra en 0
    , puntajePapel(0) // Inicializar puntaje papel en 0
    , mira(nullptr) // Inicializar la mira como nullptr
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    connect(ui->piedra, &QPushButton::clicked, this, &MainWindow::agregarPiedra);
    connect(ui->papel, &QPushButton::clicked, this, &MainWindow::agregarPapel);
    connect(ui->tijera, &QPushButton::clicked, this, &MainWindow::agregarTijera);
    connect(ui->ingresarJugador, &QPushButton::clicked, this, &MainWindow::ingresarJugador);
    connect(ui->inicio, &QPushButton::clicked, this, &MainWindow::iniciarJuego);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarTiempo);
    connect(autoCreateTimer, &QTimer::timeout, this, &MainWindow::crearObjetosAutomaticamente);

    // Inicializar las secciones de puntajes
    ui->puntajeTijeras->display(puntajeTijeras);
    ui->puntajePiedra->display(puntajePiedra);
    ui->puntajePapel->display(puntajePapel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
}

void MainWindow::agregarPiedra() {
    if (scene->items().size() < 5) {
        QPixmap piedraSprite(":/Objetos/piedra.png");
        QGraphicsPixmapItem *piedraItem = new QGraphicsPixmapItem(piedraSprite);
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - piedraSprite.width());
        int posY = 0;
        piedraItem->setPos(posX, posY);
        if (!verificarColision(piedraItem)) {
            scene->addItem(piedraItem);
            actualizarPuntaje(10, "piedra");

            // Crear un temporizador para mover la piedra
            QTimer *timerPiedra = new QTimer(this);
            connect(timerPiedra, &QTimer::timeout, this, &MainWindow::moverPiedra);
            timerPiedra->start(50);
        } else {
            delete piedraItem;
        }
    }
}

void MainWindow::agregarPapel() {
    if (scene->items().size() < 5) {
        QPixmap papelSprite(":/Objetos/papel.png");
        QGraphicsPixmapItem *papelItem = new QGraphicsPixmapItem(papelSprite);
        int posX = 0;
        int posY = 0;
        papelItem->setPos(posX, posY);
        if (!verificarColision(papelItem)) {
            scene->addItem(papelItem);
            actualizarPuntaje(20, "papel");

            // Crear un temporizador para mover el papel
            QTimer *timerPapel = new QTimer(this);
            connect(timerPapel, &QTimer::timeout, this, &MainWindow::moverPapel);
            timerPapel->start(50);
        } else {
            delete papelItem;
        }
    }
}

void MainWindow::agregarTijera() {
    if (scene->items().size() < 5) {
        QPixmap tijeraSprite(":/Objetos/tijera.png");
        QGraphicsPixmapItem *tijeraItem = new QGraphicsPixmapItem(tijeraSprite);
        int posX = 0;
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - tijeraSprite.height());
        tijeraItem->setPos(posX, posY);
        if (!verificarColision(tijeraItem)) {
            scene->addItem(tijeraItem);
            actualizarPuntaje(30, "tijeras");

            // Crear un temporizador para mover la tijera
            QTimer *timerTijera = new QTimer(this);
            connect(timerTijera, &QTimer::timeout, this, &MainWindow::moverTijeras);
            timerTijera->start(50);
        } else {
            delete tijeraItem;
        }
    }
}

void MainWindow::agregarMira() {
    QPixmap miraSprite(":/Objetos/mira.png");
    mira = new QGraphicsPixmapItem(miraSprite);
    int posX = ui->graphicsView->width() / 2 - miraSprite.width() / 2;
    int posY = ui->graphicsView->height() / 2 - miraSprite.height() / 2;
    mira->setPos(posX, posY);
    mira->setZValue(1); // Asegurar que la mira esté en la capa superior
    scene->addItem(mira);
}

void MainWindow::moverJugador(int dx, int dy) {
    if (mira) {
        mira->moveBy(dx, dy);
    }
}

// Mover la mira
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

void MainWindow::iniciarJuego() {

    tiempoRestante = 300; // Tiempo inicial en segundos
    actualizarTiempo(); // Lógica para iniciar el juego
    timer->start(1000); // Iniciar el temporizador con un intervalo de 1 segundo
    // Llamar a la función para crear objetos automáticamente
        crearObjetosAutomaticamente();

        // Iniciar autoCreateTimer para crear objetos automáticamente cada 10 segundos
        autoCreateTimer->start(1000);


}

void MainWindow::ingresarJugador() {
    agregarMira();
    tiempoRestante = 300; // 5 minutos en segundos
    //ui->tiempoLabel->display(tiempoRestante); // Mostrar el tiempo restante
    timer->start(1000); // Iniciar el temporizador con intervalo de 1 segundo

    autoCreateTimer->start(10000); // Iniciar el temporizador para crear objetos automáticamente cada 10 segundos

    // Llamar a la función para crear objetos automáticamente cada 10 segundos
    QTimer *crearObjetosTimer = new QTimer(this);
    connect(crearObjetosTimer, &QTimer::timeout, this, &MainWindow::crearObjetosAutomaticamente);
    crearObjetosTimer->start(10000); // Intervalo de 10 segundos

    // Deshabilitar botones
    ui->piedra->setDisabled(true);
    ui->papel->setDisabled(true);
    ui->tijera->setDisabled(true);
    ui->ingresarJugador->setDisabled(true);
    ui->inicio->setDisabled(true);
}

void MainWindow::actualizarTiempo() {
    tiempoRestante--;
    ui->tiempoLabel->display(tiempoRestante);

    if (tiempoRestante <= 0) {
        timer->stop();
        QMessageBox::information(this, "Fin de juego", "Se acabó el tiempo. ¡Juego terminado!");
    autoCreateTimer->stop(); // Detener autoCreateTimer cuando se acabe el tiempo
    }
}

void MainWindow::atacarObjeto() {
    if (mira) {
        foreach (QGraphicsItem *item, scene->items()) {
            if (item != mira && item->collidesWithItem(mira)) {
                scene->removeItem(item);

                QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item);
                if (pixmapItem) {
                    QPixmap pixmap = pixmapItem->pixmap();

                    if (pixmap.cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) {
                        actualizarPuntaje(50, "tijeras");
                    } else if (pixmap.cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
                        actualizarPuntaje(50, "piedra");
                    } else if (pixmap.cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
                        actualizarPuntaje(50, "papel");
                    }
                }

                delete item;
                break;
            }
        }
    }
}

void MainWindow::actualizarPuntaje(int cambio, const QString &tipo) {
    puntaje += cambio;
    ui->puntajeLabel->display(puntaje);

    if (tipo == "tijeras") {
        puntajeTijeras += cambio;
        ui->puntajeTijeras->display(puntajeTijeras);
    } else if (tipo == "piedra") {
        puntajePiedra += cambio;
        ui->puntajePiedra->display(puntajePiedra);
    } else if (tipo == "papel") {
        puntajePapel += cambio;
        ui->puntajePapel->display(puntajePapel);
    }
}

bool MainWindow::verificarColision(QGraphicsPixmapItem *item) {
    foreach (QGraphicsItem *other, scene->items()) {
        if (item->collidesWithItem(other)) {
            return true;
        }
    }
    return false;
}

void MainWindow::moverTijeras() {
    foreach (QGraphicsItem *item, scene->items()) {
        QGraphicsPixmapItem *tijeraItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (tijeraItem && tijeraItem->pixmap().cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) {
            tijeraItem->moveBy(10, 0);
        }
    }
}

void MainWindow::moverPiedra() {
    foreach (QGraphicsItem *item, scene->items()) {
        QGraphicsPixmapItem *piedraItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (piedraItem && piedraItem->pixmap().cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
            piedraItem->moveBy(0, 10);
        }
    }
}

void MainWindow::moverPapel() {
    foreach (QGraphicsItem *item, scene->items()) {
        QGraphicsPixmapItem *papelItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (papelItem && papelItem->pixmap().cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
            papelItem->moveBy(10, 10);
        }
    }
}

void MainWindow::crearObjetosAutomaticamente() {
    if (scene->items().size() < 5) {
        // Generar un número aleatorio entre 0 y 2 para determinar el tipo de objeto a crear
        int tipoObjeto = QRandomGenerator::global()->bounded(3);

        // Crear el objeto según el tipo aleatorio
        switch (tipoObjeto) {
            case 0:
                agregarPiedra();
                break;
            case 1:
                agregarPapel();
                break;
            case 2:
                agregarTijera();
                break;
        }
    }
}
