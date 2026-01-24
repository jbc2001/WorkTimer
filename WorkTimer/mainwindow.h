#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QDate>
#include <QChronoTimer>
#include <QStandardPaths>
#include <QDebug>
#include "filehandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plus5s_clicked();

    void on_plus1m_clicked();

    void on_plus5m_clicked();

    void on_minus5s_clicked();

    void on_StartStop_clicked();

    void on_minus1s_clicked();

    void on_minus5m_clicked();

    int LoadTime();
    
    void SaveTime();

    long GetTime();

    void TimerStop();

    void TimerStart();

private:
    QChronoTimer* timer = nullptr;  //timer for updating currentTime
    FileHandler* handler;   //file handler. Prevents creation of multiple
    QString path;   //path to folder storing log file
    QString fileName = "worklog";   // file name for log
    int currentTime = 0;    //time tracker in seconds
    QDateTime cycleStart; //tracks time at start of current cycle

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
