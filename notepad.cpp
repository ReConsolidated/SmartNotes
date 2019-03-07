#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    config = FileManager::loadConfig();

    if (!QDir("Notes").exists())
    {
        QDir().mkdir("Notes");
    }

    if (config.size() > 0)
    {
        currentFileName = config["LastOpenedFile"];
    }
    else
    {
        currentFileName = FileManager::makeNewFile();
        qDebug() << currentFileName;
        config.insert("LastOpenedFile", currentFileName);
        FileManager::saveConfig(config);
    }
    FileManager::fulfilListWidgetFromFile(ui->listWidget, currentFileName);

    ui->listWidget->scrollToBottom();


}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_lineEdit_returnPressed()
{
    if (bEditMode)
    {
        ui->listWidget->takeItem(editedItemRow);
        ui->listWidget->insertItem(editedItemRow, ui->lineEdit->text());
    }
    else
    {
        ui->listWidget->insertItem(ui->listWidget->count(), ui->lineEdit->text());
    }
    ui->listWidget->scrollToBottom();
    ui->listWidget->clearSelection();
    ui->lineEdit->clear();
    bEditMode = false;
    QStringList t_list;

    FileManager::saveListWidgetToFile(ui->listWidget, QString(currentFileName));
}

void Notepad::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
    bEditMode = true;
    editedItemRow = ui->listWidget->currentRow();
    ui->lineEdit->setFocus();
}



void Notepad::on_actionNowy_triggered()
{
    FileManager::saveListWidgetToFile(ui->listWidget, currentFileName);
    currentFileName = FileManager::makeNewFile();
    FileManager::fulfilListWidgetFromFile(ui->listWidget, currentFileName);
    ui->lineEdit->clear();
    config.insert("LastOpenedFile", currentFileName);
    FileManager::saveConfig(config);

}

void Notepad::on_actionOtworz_triggered()
{
    FileManager::saveListWidgetToFile(ui->listWidget, currentFileName);
    QString openedFileName = QFileDialog::getOpenFileName(this,
        tr("Otwórz inteligentną notatkę"), "Notes/", tr("Text Files (*.txt)"));
    if (openedFileName.size() > 0)
    {
        currentFileName = openedFileName;
        FileManager::fulfilListWidgetFromFile(ui->listWidget, currentFileName);
        ui->listWidget->scrollToBottom();
        ui->lineEdit->clear();
        config.insert("LastOpenedFile", currentFileName);
        FileManager::saveConfig(config);
    }

}


void Notepad::on_actionWyj_cie_triggered()
{
    QCoreApplication::quit();
}
