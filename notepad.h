#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMap>
#include <QString>

#include "filemanager.h"


namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_lineEdit_returnPressed();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionNowy_triggered();

    void on_actionOtworz_triggered();


    void on_actionWyj_cie_triggered();

private:
    Ui::Notepad *ui;
    QString currentFileName = "";
    bool bEditMode = false;
    int editedItemRow;
    QMap<QString, QString> config;
};

#endif // NOTEPAD_H
