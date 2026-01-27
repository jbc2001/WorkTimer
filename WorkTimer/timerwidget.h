#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTime>
#include <QDate>
#include <QChronoTimer>
#include <QStandardPaths>
#include <QDebug>
#include "filehandler.h"

namespace Ui {
    class TimerWidget;
}

class TimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget *parent = nullptr, QString name = "INVALID", QString path = "");
    ~TimerWidget();


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
    QString fileName = "INVALID";   // file name for log
    QString path;   //path to folder storing log file
    int currentTime = 0;    //time tracker in seconds
    QDateTime cycleStart; //tracks time at start of current cycle
    Ui::TimerWidget *ui;
};

#endif // TIMERWIDGET_H
