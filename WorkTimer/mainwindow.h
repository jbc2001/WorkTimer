#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include "timerwidget.h"
#include "titleinput.h"

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
    void CreateTimer(QString);

    void on_tabWidget_currentChanged(int index);

    void on_DeleteTimer_clicked();

    void on_OpenFolder_clicked();

private:
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/WorkTimer";   //path to folder storing log file
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
