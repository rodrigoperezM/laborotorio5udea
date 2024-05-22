
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void agregarPiedra();
    void agregarPapel();
    void agregarTijera();
    void agregarMira();
    void ingresarJugador();
    void iniciarJuego();
    void actualizarTiempo();
    void atacarObjeto();
    void moverJugador(int dx, int dy);
    void moverTijeras();
    void moverPiedra();
    void moverPapel();
    void actualizarPuntaje(int cambio, const QString &tipo);
    void crearObjetosAutomaticamente();


private:
    bool verificarColision(QGraphicsPixmapItem *item);
    //void deshabilitarBotones();
    QTimer *autoCreateTimer; // Temporizador para crear objetos automáticamente

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    int tiempoRestante;
    int puntaje;
    int puntajeTijeras;
    int puntajePiedra;
    int puntajePapel;
    QGraphicsPixmapItem *mira;
};

#endif // MAINWINDOW_H

