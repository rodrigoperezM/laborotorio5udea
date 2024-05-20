
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void agregarPiedra();
    void agregarPapel();
    void agregarTijera();
    void ingresarJugador();
    void iniciarJuego();
    void actualizarTiempo();
    void crearObjetosAutomaticamente();
    void moverJugador(int dx, int dy);
    void atacarObjeto();
    void actualizarPuntaje(int cambio);
    void deshabilitarBotones();
    bool verificarColision(QGraphicsPixmapItem *item);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    int tiempoRestante;
    int puntaje;
    QGraphicsPixmapItem *mira; // Agregar la mira como miembro de la clase
};

#endif // MAINWINDOW_H

