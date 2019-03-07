#include "filemanager.h"

FileManager::FileManager()
{

}

bool FileManager::saveConfig(QMap<QString, QString> config)
{
    QFile configFile("config.txt");
    if (!configFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not write to file: config.txt\nError string:" << configFile.errorString();
        return false;
    }

    QDataStream out(&configFile);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << config;
    return true;
}

QMap<QString, QString> FileManager::loadConfig()
{
    QFile configFile("config.txt");
    QMap<QString, QString> map;
    QDataStream in(&configFile);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    if (!configFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not write to file: config.txt\nError string:" << configFile.errorString();
        return map;
    }

    in >> map;
    return map;
}


bool FileManager::saveListWidgetToFile(QListWidget *list, QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QFile::Text | QIODevice::Truncate))
    {
        qDebug() << "File opened";
        QTextStream stream(&file);
        for (int i = 0; i<list->count();i++)
        {
            stream << list->item(i)->text() << endl;
        }
        file.close();
        return true;
    }
    qDebug() << "Couldn't open file: " << filename;
    return false;
}

bool FileManager::fulfilListWidgetFromFile(QListWidget *list, QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    list->clear();
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        list->addItem(line);
    }
    return true;
}

QString FileManager::makeNewFile()
{
    QDir directory("Notes");
    QStringList files;
    int i = 0;
    do
    {
        i++;
        files = directory.entryList(QStringList() << "note"+QString::number(i)+".txt", QDir::Files);
    } while (files.size() > 0);
    QFile newFile("Notes/note"+QString::number(i)+".txt");
    newFile.open(QIODevice::WriteOnly | QIODevice::Text);
    for (int i = 0; i<6; i++)
    {
        newFile.write("\n");
    }
    return newFile.fileName();
}
