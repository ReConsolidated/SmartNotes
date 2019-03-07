#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QListWidget>
#include <QFileInfo>
#include <QDir>
#include <QMap>

class FileManager
{
public:
    FileManager();
    static bool saveConfig(QMap<QString, QString> config);
    static QMap<QString, QString> loadConfig();
    static bool saveListWidgetToFile(QListWidget *list, QString filename);
    static bool fulfilListWidgetFromFile(QListWidget *list, QString filename);
    static QString makeNewFile();
};

#endif // FILEMANAGER_H
