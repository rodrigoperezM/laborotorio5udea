
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
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *autoCreateTimer;
    int tiempoRestante;
    int puntaje;
    int puntajeTijeras;
    int puntajePiedra;
    int puntajePapel;
    int puntajeLabel;
    QGraphicsPixmapItem *mira;
    QMap<QGraphicsPixmapItem*, QPointF> direcciones;
    // Declara un objeto QMediaPlayer como miembro de tu clase MainWindow
    QMediaPlayer *player;


    int contarObjetos(const QString &tipo);
    void mostrarInstrucciones();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H*/
