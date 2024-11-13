#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(){}
    ~Worker(){}

signals:
    void finished();

public slots:
    void process(int duration);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    QThread * function1;
    QThread * function2;

    Worker *worker1;
    Worker *worker2;

    void startF1();
    void startF2();
    void start();
};
#endif // MAINWINDOW_H
