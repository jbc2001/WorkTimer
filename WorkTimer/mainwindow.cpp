#include "mainwindow.h"
#include "./ui_mainwindow.h"

//Loads the saved time from the worklog file for the current day and returns value if found otherwise 0
int MainWindow::LoadTime(){

    //gets path to desktop. Change to whatever address is preferred.
    path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    //initialize file handler
    handler = new FileHandler();

    //gets current date as QString
    QString date = QDate::currentDate().toString("yyyy/MM/dd");

    //reads the raw text file into a QString
    QString rawText = QString::fromStdString(handler->ReadText(fileName, path));

    //splits the file string into lines
    QStringList lines = rawText.split('\n');

    if(lines.size()>0){
        //gets the last line (should be current date or older)
        QString finalLine = lines.last();

        //checks if the line matches the current date
        if(lines.last().contains(date)){
            int start = finalLine.indexOf('{');
            int end = finalLine.indexOf('}',start);

            //extracts the integer value inside the braces and sets the current time value to it
            if(start != -1 && end != -1 && end > start){
                currentTime = finalLine.mid(start+1,end-start-1).toInt();
                return currentTime;
            }
        }
    }
    return 0;
}

//saves the currentTime value to file as well as human readable form
void MainWindow::SaveTime(){
    //gets current date as QString
    QString date = QDate::currentDate().toString("yyyy/MM/dd");

    //reads the existing file into a QString
    QString rawText = QString::fromStdString(handler->ReadText(fileName, path));

    //splits file string into lines
    QStringList lines = rawText.split('\n');

    //finds the index of the last non empty line
    int lastIndex = lines.size() - 1;
    while(lastIndex >= 0 && lines[lastIndex].trimmed().isEmpty()){
        lastIndex--;
    }

    //removes the line containing todays date if it exists. This prevents duplicate of todays entry
    if(lastIndex >= 0 && lines[lastIndex].contains(date)) {
        lines.removeAt(lastIndex); // remove the last line
    }

    //creates todays entry
    QString today = QString("Date: %1, Hours: %2, Minutes: %3\t\t raw: {%4}")
                        .arg(date)
                        .arg(currentTime/3600)      //hours
                        .arg((currentTime%3600)/60) //minutes
                        .arg(currentTime);          //seconds

    //appends todays date to lines list
    lines.append(today);

    //joins lines back together as single string seperated by newline
    QString fileData = lines.join('\n');

    //saves the content back to the file
    handler->SaveText(fileName,path,fileData);
}

//returns time as a string in the format used by the timer
QString SecondsToTimeString(int intTime){
    int hours = intTime / 3600;
    int minutes = (intTime % 3600) / 60;
    int seconds = intTime % 60;
    //converts and combines time ints into time string
    QString output = QString("%1:%2:%3")
                         .arg(hours,2,10,QChar('0'))
                         .arg(minutes,2,10,QChar('0'))
                         .arg(seconds,2,10,QChar('0'));
    return output;
}

//Initializes program
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialise currentTime to saved value
    int InitialTime = LoadTime();

    //updates timer text to initial time
    this->ui->Time->setText(SecondsToTimeString(InitialTime));

    //creates new timer with 1 second interval
    timer = new QChronoTimer(this);
    std::chrono::seconds interval{1};
    timer->setInterval(interval);

    //function called by timer
    timer->callOnTimeout(this,[this](){
        //increment time and update text
        ++currentTime;
        this->ui->Time->setText(SecondsToTimeString(currentTime));
    });
}

//destructor: saves time and cleans up UI resources
MainWindow::~MainWindow()
{
    SaveTime();
    delete ui;
}

//start stop button
void MainWindow::on_StartStop_clicked()
{
    //starts timer and changes button text to Stop
    if(!timer->isActive()){
        timer->start();
        ui->StartStop->setText("Stop");

    }
    //stops timer and changes button text to Start
    else{
        timer->stop();
        ui->StartStop->setText("Start");
        SaveTime();
    }
}

//adds 5 seconds to currentTime and updates UI
void MainWindow::on_plus5s_clicked()
{
    currentTime+=5;
    this->ui->Time->setText(SecondsToTimeString(currentTime));

}

//adds 1 minute to currentTime and updates UI
void MainWindow::on_plus1m_clicked()
{
    currentTime+=60;
    this->ui->Time->setText(SecondsToTimeString(currentTime));

}

//adds 5 minutes to currentTime and updates UI
void MainWindow::on_plus5m_clicked()
{
    currentTime+=300;
    this->ui->Time->setText(SecondsToTimeString(currentTime));

}

//subtracts 5 seconds from currentTime and updates UI
void MainWindow::on_minus5s_clicked()
{
    //clamps minimum value to 0
    if(currentTime-5<0){
        currentTime=0;
    }
    else{
        currentTime -= 5;
    }
    this->ui->Time->setText(SecondsToTimeString(currentTime));

}

//subtracts 1 minute from currentTime and updates UI
void MainWindow::on_minus1s_clicked()
{
    //clamps minimum value to 0
    if(currentTime-60<0){
        currentTime=0;
    }
    else{
        currentTime -= 60;
    }
    this->ui->Time->setText(SecondsToTimeString(currentTime));
}

//subtracts 5 minutes from currentTime and updates UI
void MainWindow::on_minus5m_clicked()
{
    //clamps minimum value to 0
    if(currentTime-300<0){
        currentTime=0;
    }
    else{
        currentTime -= 300;
    }
    this->ui->Time->setText(SecondsToTimeString(currentTime));
}

