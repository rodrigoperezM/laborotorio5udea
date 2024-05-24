
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QMediaPlayer>

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
    , puntajeLabel(0)
    , mira(nullptr) // Inicializar la mira como nullptr

{

    // En el constructor de tu clase MainWindow, inicializa el objeto QMediaPlayer

    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new QMediaPlayer(this);

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

    // Mostrar mensaje con instrucciones
        QMessageBox::information(this, "Bienvenido al juego PIEDRA, PAPEL O TIJERA",
            "Instrucciones del Juego\n",
            "1-Usa W, A, S, D para mover la mira.\n"
            "2-Presiona Espacio para atacar objetos.\n"
            "3-El objetivo es destruir tantos objetos como puedas.\n"
            "4-Puedes agregar piedras, papeles o tijeras usando los botones correspondientes.\n"
            "5-El juego termina cuando se acaba el tiempo.\n"
            "¡Disfruta del juego y diviertete!");
}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;


}

int MainWindow::contarObjetos(const QString &tipo) {
    int count = 0;
    foreach (QGraphicsItem *item, scene->items()) {
        QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (pixmapItem) {
            QPixmap pixmap = pixmapItem->pixmap();
            if ((tipo == "tijeras" && pixmap.cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) ||
                (tipo == "piedra" && pixmap.cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) ||
                (tipo == "papel" && pixmap.cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey())) {
                count++;
            }
        }
    }
    return count;
}


void MainWindow::agregarPiedra() {
    if (scene->items().count() < 5) {
        QPixmap piedraSprite(":/Objetos/piedra.png");
        QGraphicsPixmapItem *piedraItem = new QGraphicsPixmapItem(piedraSprite);
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - piedraSprite.width());
        int posY = 0;
        piedraItem->setPos(posX, posY);
        if (!verificarColision(piedraItem)) {
            scene->addItem(piedraItem);
            direcciones[piedraItem] = QPointF(0, 10); // Inicializar dirección
            //actualizarPuntaje(1, "piedra");

            // Crear un temporizador para mover la piedra
            QTimer *timerPiedra = new QTimer(this);
            connect(timerPiedra, &QTimer::timeout, this, &MainWindow::moverPiedra);
            timerPiedra->start(80);
        } else {
            //delete piedraItem;
        }
    }
}

void MainWindow::agregarPapel() {
    if (scene->items().count() < 5) {
        QPixmap papelSprite(":/Objetos/papel.png");
        QGraphicsPixmapItem *papelItem = new QGraphicsPixmapItem(papelSprite);
        int posX = 0;
        int posY = 0;
        papelItem->setPos(posX, posY);
        if (!verificarColision(papelItem)) {
            scene->addItem(papelItem);
            direcciones[papelItem] = QPointF(10,10); // Inicializar dirección
            //actualizarPuntaje(1, "papel");

            // Crear un temporizador para mover el papel
            QTimer *timerPapel = new QTimer(this);
            connect(timerPapel, &QTimer::timeout, this, &MainWindow::moverPapel);
            timerPapel->start(80);
        } else {
            //delete papelItem;
        }
    }
}

void MainWindow::agregarTijera() {
    if (scene->items().count() < 5) {
        QPixmap tijeraSprite(":/Objetos/tijera.png");
        QGraphicsPixmapItem *tijeraItem = new QGraphicsPixmapItem(tijeraSprite);
        int posX = 0;
        int posY = 0;
        tijeraItem->setPos(posX, posY);
        if (!verificarColision(tijeraItem)) {
            scene->addItem(tijeraItem);
            direcciones[tijeraItem] = QPointF(10, 0); // Inicializar dirección
            //actualizarPuntaje(1, "tijeras");

            // Crear un temporizador para mover la tijera
            QTimer *timerTijera = new QTimer(this);
            connect(timerTijera, &QTimer::timeout, this, &MainWindow::moverTijeras);
            timerTijera->start(80);
        } else {
            //delete tijeraItem;
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

    //tiempoRestante = 300; // Tiempo inicial en segundos
    //actualizarTiempo(); // Lógica para iniciar el juego
    //timer->start(1000); // Iniciar el temporizador con un intervalo de 1 segundo
    // Llamar a la función para crear objetos automáticamente
        crearObjetosAutomaticamente();

        // Iniciar autoCreateTimer para crear objetos automáticamente cada 10 segundos
        autoCreateTimer->start(1000);


}

void MainWindow::ingresarJugador() {
    agregarMira();
    tiempoRestante = 300; // 5 minutos en segundos
    ui->tiempoLabel->display(tiempoRestante); // Mostrar el tiempo restante
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
        autoCreateTimer->stop(); // Detener autoCreateTimer cuando se acabe el tiempo

        // Determinar el ganador basado en el puntaje
        QString ganador;
        int puntajeMaximo = qMax(puntajeTijeras, qMax(puntajePiedra, puntajePapel));
        if (puntajeMaximo == puntajeTijeras) {
            ganador = "Tijeras";
        } else if (puntajeMaximo == puntajePiedra) {
            ganador = "Piedras";
        } else if (puntajeMaximo == puntajePapel) {
            ganador = "Papeles";
        }

        // Verificar si el jugador tiene el puntaje máximo
               if (puntajeMaximo == puntajeLabel) {
                   ganador = "el jugador";
               }
        QMessageBox::information(this, "Fin de juego", "Se acabó el tiempo. ¡Juego terminado!\n"
                                 "El ganador es: " + ganador);
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
                        actualizarPuntaje(1, "puntajeLabel");
                        ui->puntajeLabel->display(puntaje);
                        //actualizarPuntaje(1, "tijeras");
                    } else if (pixmap.cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
                        actualizarPuntaje(1, "puntajeLabel");
                        ui->puntajeLabel->display(puntaje);

                    } else if (pixmap.cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
                        actualizarPuntaje(1, "puntajeLabel");
                        ui->puntajeLabel->display(puntaje);

                    }
                }

                player->setMedia(QUrl("qrc:/sonido.mp3"));
                   player->play();


                //delete item;
                return;
            }
        }
    }
}

void MainWindow::actualizarPuntaje(int puntos, const QString &tipo) {
    if (tipo == "tijeras") {
        puntajeTijeras += puntos;
       ui->puntajeTijeras->display(puntajeTijeras);
    } else if (tipo == "piedra") {
        puntajePiedra += puntos;
        ui->puntajePiedra->display(puntajePiedra);
    } else if (tipo == "papel") {
        puntajePapel += puntos;
        ui->puntajePapel->display(puntajePapel);
    }

    puntaje += puntos;
    //ui->puntajeLabel->display(puntaje);
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
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *tijeraItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (tijeraItem && tijeraItem->pixmap().cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) {
            QPointF direccion = direcciones[tijeraItem];
            tijeraItem->moveBy(direccion.x(), direccion.y());

            // Verificar colisiones con otros objetos
            QList<QGraphicsItem *> colisiones = tijeraItem->collidingItems();
            for (QGraphicsItem *otroItem : colisiones) {
                QGraphicsPixmapItem *otroPixmapItem = dynamic_cast<QGraphicsPixmapItem *>(otroItem);
                if (otroPixmapItem && otroPixmapItem != tijeraItem) {
                    QPixmap otroPixmap = otroPixmapItem->pixmap();
                    if (otroPixmap.cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
                        // Tijeras destruyen papel
                        scene->removeItem(otroPixmapItem);
                        actualizarPuntaje(1, "tijeras");
                        //delete otroPixmapItem;
                    } else if (otroPixmap.cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
                        // Piedra destruye tijeras
                        scene->removeItem(tijeraItem);
                        actualizarPuntaje(1, "piedra");
                        //delete tijeraItem;
                        break;
                    }
                }
            }

            // Rebotar en los bordes de la pantalla
            if (tijeraItem->x() <= 0 || tijeraItem->x() + tijeraItem->pixmap().width() >= ui->graphicsView->width()) {
                direccion.setX(-direccion.x());
            }
            if (tijeraItem->y() <= 0 || tijeraItem->y() + tijeraItem->pixmap().height() >= ui->graphicsView->height()) {
                direccion.setY(-direccion.y());
            }
            direcciones[tijeraItem] = direccion;
        }
    }
}

void MainWindow::moverPiedra() {
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *piedraItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (piedraItem && piedraItem->pixmap().cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
            QPointF direccion = direcciones[piedraItem];
            piedraItem->moveBy(direccion.x(), direccion.y());

            // Verificar colisiones con otros objetos
            QList<QGraphicsItem *> colisiones = piedraItem->collidingItems();
            for (QGraphicsItem *otroItem : colisiones) {
                QGraphicsPixmapItem *otroPixmapItem = dynamic_cast<QGraphicsPixmapItem *>(otroItem);
                if (otroPixmapItem && otroPixmapItem != piedraItem) {
                    QPixmap otroPixmap = otroPixmapItem->pixmap();
                    if (otroPixmap.cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) {
                        // Piedra destruye tijeras
                        scene->removeItem(otroPixmapItem);
                        actualizarPuntaje(1, "piedra");
                        //delete otroPixmapItem;
                    } else if (otroPixmap.cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
                        // Papel destruye piedra
                        scene->removeItem(piedraItem);
                        actualizarPuntaje(1, "papel");
                        //delete piedraItem;
                        break;
                    }
                }
            }

            // Rebotar en los bordes de la pantalla
            if (piedraItem->x() <= 0 || piedraItem->x() + piedraItem->pixmap().width() >= ui->graphicsView->width()) {
                direccion.setX(-direccion.x());
            }
            if (piedraItem->y() <= 0 || piedraItem->y() + piedraItem->pixmap().height() >= ui->graphicsView->height()) {
                direccion.setY(-direccion.y());
            }
            direcciones[piedraItem] = direccion;
        }
    }
}

void MainWindow::moverPapel() {
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *papelItem = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (papelItem && papelItem->pixmap().cacheKey() == QPixmap(":/Objetos/papel.png").cacheKey()) {
            QPointF direccion = direcciones[papelItem];
            papelItem->moveBy(direccion.x(), direccion.y());

            // Verificar colisiones con otros objetos
            QList<QGraphicsItem *> colisiones = papelItem->collidingItems();
            for (QGraphicsItem *otroItem : colisiones) {
                QGraphicsPixmapItem *otroPixmapItem = dynamic_cast<QGraphicsPixmapItem *>(otroItem);
                if (otroPixmapItem && otroPixmapItem != papelItem) {
                    QPixmap otroPixmap = otroPixmapItem->pixmap();
                    if (otroPixmap.cacheKey() == QPixmap(":/Objetos/piedra.png").cacheKey()) {
                        // Papel destruye piedra
                        scene->removeItem(otroPixmapItem);
                        actualizarPuntaje(1, "papel");
                        //delete otroPixmapItem;
                    } else if (otroPixmap.cacheKey() == QPixmap(":/Objetos/tijera.png").cacheKey()) {
                        // Tijeras destruyen papel
                        scene->removeItem(papelItem);
                        actualizarPuntaje(1, "tijeras");
                        //delete papelItem;
                        break;
                    }
                }
            }

            // Rebotar en los bordes de la pantalla
            if (papelItem->x() <= 0 || papelItem->x() + papelItem->pixmap().width() >= ui->graphicsView->width()) {
                direccion.setX(-direccion.x());
            }
            if (papelItem->y() <= 0 || papelItem->y() + papelItem->pixmap().height() >= ui->graphicsView->height()) {
                direccion.setY(-direccion.y());
            }
            direcciones[papelItem] = direccion;
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
