#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
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

private slots:
    void agregarTijera();
    void agregarPiedra();
    void agregarPapel();
    void ingresarJugador();
    void iniciarJuego();
    void actualizarTiempo();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
private:
    int tiempoRestante; // Variable para almacenar el tiempo restante en segundos

};
#endif // MAINWINDOW_H
