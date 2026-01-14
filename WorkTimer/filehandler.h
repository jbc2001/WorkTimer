#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>

class FileHandler
{
    bool EnsureFolderExists(const QString &folderPath);


public:
    void SaveText(QString name, QString path, QString text);
    std::string ReadText(QString name, QString path);
};

#endif // FILEHANDLER_H
