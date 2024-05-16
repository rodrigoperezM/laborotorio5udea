// Implementación de las funciones de MainWindow
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    tiempoRestante(300) // 5 minutos en segundos
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);

    connect(ui->piedra, &QPushButton::clicked, this, &MainWindow::agregarPiedra);
    connect(ui->papel, &QPushButton::clicked, this, &MainWindow::agregarPapel);
    connect(ui->tijera, &QPushButton::clicked, this, &MainWindow::agregarTijera);
    connect(ui->jugador, &QPushButton::clicked, this, &MainWindow::ingresarJugador);
    connect(ui->inicio, &QPushButton::clicked, this, &MainWindow::iniciarJuego);

    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarTiempo);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
}

/*Esta función elige una posición aleatoria para la piedra en el eje X
y luego decide si aparecerá en la parte superior o inferior de la escena
con base en otro número aleatorio.
Luego establece la posición Y de acuerdo a esa decisión.*/

void MainWindow::agregarPiedra() {
    // Verificar si ya hay 5 piedras en la escena
    if (scene->items().size() < 5) {
        QPixmap piedraSprite(":/Objetos/piedra.png");
        QGraphicsPixmapItem *piedraItem = new QGraphicsPixmapItem(piedraSprite);

        // Generar posición aleatoria para la piedra
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - piedraSprite.width());
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - piedraSprite.height());

        // Decidir si la piedra aparecerá arriba o abajo en la escena
        if (QRandomGenerator::global()->bounded(2) == 0) { // 0 para arriba, 1 para abajo
            posY = 0; // Aparece en la parte superior
        } else {
            posY = ui->graphicsView->height() - piedraSprite.height(); // Aparece en la parte inferior
        }

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

        // Decidir la esquina en la que aparecerá el papel
        int corner = QRandomGenerator::global()->bounded(4); // Número aleatorio entre 0 y 3
        switch (corner) {
            case 0: // Esquina superior izquierda
                posX = 0;
                posY = 0;
                break;
            case 1: // Esquina superior derecha
                posX = ui->graphicsView->width() - papelSprite.width();
                posY = 0;
                break;
            case 2: // Esquina inferior izquierda
                posX = 0;
                posY = ui->graphicsView->height() - papelSprite.height();
                break;
            case 3: // Esquina inferior derecha
                posX = ui->graphicsView->width() - papelSprite.width();
                posY = ui->graphicsView->height() - papelSprite.height();
                break;
        }

        // Añadir el papel a la escena
        scene->addItem(papelItem);
        papelItem->setPos(posX, posY);
    }
}


/*Esta función elige una posición aleatoria para las tijeras en el eje Y y
luego decide si aparecerá en la parte derecha o izquierda de la escena con base en
otro número aleatorio. Luego establece la posición X de acuerdo a esa decisión.*/
void MainWindow::agregarTijera() {
    // Verificar si ya hay 5 tijeras en la escena
    if (scene->items().size() < 5) {
        QPixmap tijeraSprite(":/Objetos/tijera.png");
        QGraphicsPixmapItem *tijeraItem = new QGraphicsPixmapItem(tijeraSprite);

        // Generar posición aleatoria para las tijeras
        int posY = QRandomGenerator::global()->bounded(0, ui->graphicsView->height() - tijeraSprite.height());
        int posX = QRandomGenerator::global()->bounded(0, ui->graphicsView->width() - tijeraSprite.width());

        // Decidir si las tijeras aparecerán en la parte derecha o izquierda de la escena
        if (QRandomGenerator::global()->bounded(2) == 0) { // 0 para la izquierda, 1 para la derecha
            posX = 0; // Aparece en la parte izquierda
        } else {
            posX = ui->graphicsView->width() - tijeraSprite.width(); // Aparece en la parte derecha
        }

        // Añadir las tijeras a la escena
        scene->addItem(tijeraItem);
        tijeraItem->setPos(posX, posY);
    }
}


void MainWindow::ingresarJugador() {
    mostrarIndicadorJugador();
    iniciarTemporizador();
}

void MainWindow::mostrarIndicadorJugador() {
    ui->jugador->show();
}

void MainWindow::iniciarTemporizador() {
    ui->tiempoLabel->display(tiempoRestante);
    timer->start(1000);
}

void MainWindow::iniciarJuego() {
    deshabilitarBotones();
    timer->start(100); // Comenzar el temporizador con un intervalo de 100 ms
}

void MainWindow::deshabilitarBotones() {
    ui->piedra->setEnabled(false);
    ui->papel->setEnabled(false);
    ui->tijera->setEnabled(false);
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
    if (scene->items().size() < 5) {
        // Generar un número aleatorio para determinar qué tipo de objeto crear
        int tipoObjeto = QRandomGenerator::global()->bounded(3); // 0 para piedra, 1 para papel, 2 para tijera

        // Crear un objeto dependiendo del tipo generado aleatoriamente
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
        default:
            break;
        }
    }


}






