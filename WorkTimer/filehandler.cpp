#include "filehandler.h"
#include <QFile>
#include <QDebug>
#include <QDir>

//Checks if the folder exists at the path and if not creates one
bool FileHandler::EnsureFolderExists(const QString &folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists()) {

        //creates the path
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create folder:" << folderPath;
            return false;
        }
    }
    return true;
}

//returns list of all existing timer files
std::vector<QString> FileHandler::GetAvailableFiles(QString path){
    std::vector<QString> output;
    QDir dir(path);
    dir.setNameFilters({"*.txt"});
    dir.setFilter(QDir::Files);

    const QStringList files = dir.entryList();
    for(const QString &file : files){
        output.push_back(file);
    }
    return output;
}

//Saves text to path specified
void FileHandler::SaveText(QString name, QString path, QString text){

    //check folder exists
    if (!EnsureFolderExists(path)){
        return;
    }

    //create file path
    QFile file(path + "/" + name + ".txt");

    //attempts to open the file in WriteOnly mode
    if(!file.open(QIODevice::WriteOnly)){
        qWarning() << "Failed to open file for writing" << file.errorString();
        return;
    }

    //converts the QString text into utf-8 encoded data
    QByteArray data = text.toUtf8();

    //writes to file and closes it
    file.write(data);
    file.close();
}

//returns a string containing the text from the file
std::string FileHandler::ReadText(QString name, QString path){
    //check folder exists
    if(!EnsureFolderExists(path)){
        return "";
    }

    //create file path
    QFile file(path+"/"+name+".txt");

    //attempts to open file in ReadOnly mode
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Failed to open file for reading" << file.errorString();
        return "";
    }

    //reads file to byte array
    QByteArray data = file.readAll();

    //returns byte array converted to string
    return data.toStdString();
}
