#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

//Initializes program
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //gets list of available files
    FileHandler handler = FileHandler();
    std::vector<QString> existingFiles = handler.GetAvailableFiles(path);

    //creates generic timer if none exist
    if(existingFiles.empty()){
        CreateTimer("Timer");
    }

    //creates initial timers
    for(int i = 0; i < existingFiles.size(); ++i){
        //removes .txt
        existingFiles[i].chop(4);
        //creates timer tab
        CreateTimer(existingFiles[i]);
    }
    //sets view to first tab
    ui->tabWidget->setCurrentIndex(0);
}

//destructor: cleans up UI resources
MainWindow::~MainWindow()
{
    delete ui;
}

//Creates new Timer tab
void MainWindow::CreateTimer(QString name){
    //creates new timer widget and passes name to it
    TimerWidget *timer = new TimerWidget(nullptr, name, path);

    //inserts the timer tab at the start
    ui->tabWidget->insertTab(ui->tabWidget->count()-1, timer, name);
}

//handles '+' tab button
void MainWindow::on_tabWidget_currentChanged(int index){
    //checks if '+' tab is pressed
    if(ui->tabWidget->currentIndex()==ui->tabWidget->count()-1){
        //sets default name for new tab
        QString name = "INVALID";

        //creates new dialog for a title
        TitleInput input(this);
        input.setWindowTitle("Enter Name for Timer");

        //run TitleInput modally
        if(input.exec()==QDialog::Accepted){
            //gets name from input
            name = input.GetName();

            //check for empty string
            if(name.length()>=1){
                //Creates Timer
                CreateTimer(name);
            }
        }
        //selects newly created tab or goes back to last
        ui->tabWidget->setCurrentIndex(index-1);
    }
}

void MainWindow::on_DeleteTimer_clicked() {
    //check there's at least 1 timer plus the '+' tab
    if (ui->tabWidget->count() > 2) {
        //get current tab index
        int index = ui->tabWidget->currentIndex();

        //get pointer to widget to be deleted
        QWidget *widget = ui->tabWidget->widget(index);

        //go to first tab
        ui->tabWidget->setCurrentIndex(0);

        //remove tab
        ui->tabWidget->removeTab(index);

        //delete widget
        widget->deleteLater();
    }
}

void MainWindow::on_OpenFolder_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

