// En el archivo mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void agregarPiedra();
    void agregarPapel();
    void agregarTijera();
    void ingresarJugador();
    void iniciarJuego();
    void actualizarTiempo();
    void crearObjetosAutomaticamente();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    int tiempoRestante;

    void mostrarIndicadorJugador();
    void iniciarTemporizador();
    void deshabilitarBotones();
};

#endif // MAINWINDOW_H
