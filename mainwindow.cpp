// Implementación de las funciones de MainWindow

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ObjetoJuego.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRandomGenerator>
#include <QTimer>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    tiempoRestante(30) // Tiempo inicial en segundos (5 minutos)
{
    ui->setupUi(this);
    // Asignamos la escena al QGraphicsView
    ui->graphicsView->setScene(scene);

    // Conexiones de señales y slots para los botones
    connect(ui->piedra, &QPushButton::clicked, this, &MainWindow::agregarPiedra);
    connect(ui->papel, &QPushButton::clicked, this, &MainWindow::agregarPapel);
    connect(ui->tijera, &QPushButton::clicked, this, &MainWindow::agregarTijera);
    connect(ui->jugador, &QPushButton::clicked, this, &MainWindow::ingresarJugador);
    connect(ui->inicio, &QPushButton::clicked, this, &MainWindow::iniciarJuego);

    // Configuración del temporizador
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarTiempo);


    // Conexión de la señal timeout del temporizador a la función actualizarTiempo()
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarTiempo);

    // Configuración del temporizador
    timer->start(1000); // Iniciar el temporizador con intervalo de 1 segundo (1000 milisegundos)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::agregarPiedra() {
    // Verificar si ya hay 5 piedras en la escena
    if (scene->items().size() < 5) {
        QPixmap piedraSprite(":/Objetos/piedra.png");
        QGraphicsPixmapItem *piedraItem = new QGraphicsPixmapItem(piedraSprite);

        // Generar posición aleatoria para la piedra
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - piedraSprite.width());
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - piedraSprite.height());

        // Añadir la piedra a la escena
        scene->addItem(piedraItem);
        piedraItem->setPos(posX, posY);
    }
}

void MainWindow::agregarPapel() {
    // Verificar si ya hay 5 papeles en la escena
    if (scene->items().size() < 5) {
        QPixmap papelSprite(":/Objetos/papel.png");
        QGraphicsPixmapItem *papelItem = new QGraphicsPixmapItem(papelSprite);

        // Generar posición aleatoria para el papel
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - papelSprite.width());
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - papelSprite.height());

        // Añadir el papel a la escena
        scene->addItem(papelItem);
        papelItem->setPos(posX, posY);
    }
}

void MainWindow::agregarTijera() {
    // Verificar si ya hay 5 tijeras en la escena
    if (scene->items().size() < 5) {
        QPixmap tijeraSprite(":/Objetos/tijera.png");
        QGraphicsPixmapItem *tijeraItem = new QGraphicsPixmapItem(tijeraSprite);

        // Generar posición aleatoria para las tijeras
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - tijeraSprite.width());
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - tijeraSprite.height());

        // Añadir las tijeras a la escena
        scene->addItem(tijeraItem);
        tijeraItem->setPos(posX, posY);
    }
}

void MainWindow::ingresarJugador() {
    // Lógica para ingresar el nombre del jugador y mostrar el indicador
    // ...
}

void MainWindow::iniciarJuego() {
    // Lógica para iniciar el juego
    // Deshabilitar botones y activar la creación automática de objetos
    ui->piedra->setEnabled(false);
    ui->papel->setEnabled(false);
    ui->tijera->setEnabled(false);
    timer->start(100); // Comenzar el temporizador con un intervalo de 100 ms
    // Actualizar la interfaz de usuario
        // Por ejemplo, mostrar el tiempo restante
        tiempoRestante = 300; // Tiempo inicial en segundos
        actualizarTiempo();

}
void MainWindow::actualizarTiempo()
{
    // Reducir el tiempo restante en 1 segundo
    tiempoRestante--;

    // Actualizar la interfaz gráfica para reflejar el tiempo restante
    // Por ejemplo, mostrar el tiempo restante en un QLabel
    ui->tiempoLabel->display(tiempoRestante);

    // Si el tiempo restante llega a cero, detener el temporizador y mostrar el mensaje de fin de juego
    if (tiempoRestante <= 0) {
        timer->stop();
        QMessageBox::information(this, "Fin de juego", "Se acabó el tiempo. ¡Juego terminado!");
    }
}


