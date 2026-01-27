#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <vector>

class FileHandler
{
    bool EnsureFolderExists(const QString &folderPath);


public:
    void SaveText(QString name, QString path, QString text);
    std::string ReadText(QString name, QString path);
    std::vector<QString> GetAvailableFiles(QString path);
};

#endif // FILEHANDLER_H
