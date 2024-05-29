
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QMap>
#include <QPointF>
#include <QMediaPlayer>
#include "explosion.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void agregarPiedra();
    void agregarPapel();
    void agregarTijera();
    void agregarMira();
    void moverJugador(int dx, int dy);
    void iniciarJuego();
    void ingresarJugador();
    void actualizarTiempo();
    void atacarObjeto();
    void actualizarPuntaje(int cambio, const QString &tipo);
    bool verificarColision(QGraphicsPixmapItem *item);
    void moverTijeras();
    void moverPiedra();
    void moverPapel();
    void crearObjetosAutomaticamente();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;//Maneja la escena gráfica donde se muestran los objetos del juego.
    QTimer *timer;//Temporizador que controla la duración total del juego.

        QTimer *gameTimer;

    QTimer *autoCreateTimer;//Temporizador para la creación automática de objetos.
    int tiempoRestante;
    int puntaje;
    int puntajeTijeras;
    int puntajePiedra;
    int puntajePapel;
    int puntajeLabel;
    QGraphicsPixmapItem *mira;
    QMap<QGraphicsPixmapItem*, QPointF> direcciones;

    QMediaPlayer *player;//Objeto para reproducir sonidos.
    Explosion *explosion;//Objeto que maneja la animación de explosión.



    int contarObjetos(const QString &tipo);
    void mostrarInstrucciones();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H*/
