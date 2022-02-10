#include "mainwindow.h"
#include "socialtraffic.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new TrafficItemModel();

    ui->tableView->setModel(model);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isExist(int iD)
{
    QLinkedList<SocialTraffic> *subList = model->getList();
    foreach(SocialTraffic elem, *subList)
    {
        if (elem.iD == iD)
            return (true);
    }
    return (false);
}

void MainWindow::addEntry()
{
    SocialTraffic jObject;
    jObject.iD = ui->textId->toPlainText().toInt();
    jObject.siteID = ui->textSiteId->toPlainText().toInt();
    jObject.link = ui->textLink->toPlainText();
    jObject.site = ui->textSite->toPlainText();
    jObject.share = ui->textShare->toPlainText().toDouble();
    model->insert(jObject);
}

void MainWindow::on_addEntry_clicked()
{
    if ((ui->textId->toPlainText() == "") || (ui->textSiteId->toPlainText() == "") ||
        (ui->textLink->toPlainText() == "") || (ui->textSite->toPlainText() == "") ||
        (ui->textShare->toPlainText() == ""))
    {
        QMessageBox::critical(this, QString("Error on add entry"), QString("Please, insert data in textboxes"));
        return ;
    }
    if (!ui->tableView->model())
    {
        QMessageBox::critical(this, QString("Error on add entry"), QString("Your model doesn't exist"));
        return ;
    }
    if (isExist(ui->textId->toPlainText().toInt()))
    {
        QMessageBox::critical(this, QString("Error on add entry"), QString("Element with this id exist"));
        return ;
    }
    addEntry();
}

void MainWindow::on_deleteEntry_clicked()
{
    int currRow = ui->tableView->currentIndex().row();
    if (currRow < 0)
    {
        QMessageBox::critical(this, QString("Error on delete entry"), QString("Row is out of bounds"));
        return ;
    }
    model->remove(currRow);
}

void MainWindow::changeJson(SocialTraffic jObject)
{
    int current_row = ui->tableView->currentIndex().row();
    if (current_row < 0)
        return ;
    model->change(current_row, jObject);
}

void MainWindow::clearTextBox()
{
    ui->textId->clear();
    ui->textSiteId->clear();
    ui->textLink->clear();
    ui->textSite->clear();
    ui->textShare->clear();
}

void MainWindow::on_changeEntry_clicked()
{
    SocialTraffic jObject;
    jObject.iD = ui->textId->toPlainText().toInt();
    jObject.siteID = ui->textSiteId->toPlainText().toInt();
    jObject.link = ui->textLink->toPlainText();
    jObject.site = ui->textSite->toPlainText();
    jObject.share = ui->textShare->toPlainText().toDouble();
    changeJson(jObject);
}

bool MainWindow::readFile()
{
    QFile           file;
    QJsonDocument   jsonFile;
    QJsonArray      jsonArray;

    jsonPath = QFileDialog::getOpenFileName(this, tr("Read File"), QDir::currentPath(), 0, 0, QFileDialog::DontUseNativeDialog);
    file.setFileName(jsonPath);
    if (file.open(QIODevice::ReadOnly | QFile::Text))
        jsonFile = QJsonDocument::fromJson(file.readAll(), &jsonErr);
    else
    {
        QMessageBox::critical(this, QString("Error in read file"), QString("Couldn't open file"));
        return (false);
    }
    file.close();

    if (!jsonFile.isArray())
    {
        QMessageBox::critical(this, QString("Error on read file"), QString("Opened file is not json type or is empty"));
        return (false);
    }
    jsonArray = jsonFile.array();
    foreach (QJsonValue jsonValue, jsonArray)
        model->insert(jsonValue);
    return (true);
}

void MainWindow::setUIEnabled(bool bEnabled)
{
    ui->writeJson->setEnabled(bEnabled);
    ui->addEntry->setEnabled(bEnabled);
    ui->deleteEntry->setEnabled(bEnabled);
    ui->changeEntry->setEnabled(bEnabled);
    ui->textId->setEnabled(bEnabled);
    ui->textSiteId->setEnabled(bEnabled);
    ui->textSite->setEnabled(bEnabled);
    ui->textLink->setEnabled(bEnabled);
    ui->textShare->setEnabled(bEnabled);
}

void MainWindow::on_readJson_clicked()
{
    model->clearModel();
    if (!readFile())
    {
        model->clearModel();
        clearTextBox();
        setUIEnabled(false);
        return ;
    }
    setUIEnabled(true);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    clearTextBox();

    QVariant textInsert = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0));
    ui->textId->insertPlainText(textInsert.toString());
    textInsert = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1));
    ui->textSiteId->insertPlainText(textInsert.toString());
    textInsert = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2));
    ui->textLink->insertPlainText(textInsert.toString());
    textInsert = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3));
    ui->textSite->insertPlainText(textInsert.toString());
    textInsert = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4));
    ui->textShare->insertPlainText(textInsert.toString());
}

void MainWindow::on_writeJson_clicked()
{
    QFile           file;
    QJsonDocument   jsonFile;
    QJsonArray      jsonArray;
    QLinkedList<SocialTraffic> *ptrJson;

    jsonPath = QFileDialog::getSaveFileName(this, tr("Read File"), QDir::currentPath(), 0, 0, QFileDialog::DontUseNativeDialog);
    file.setFileName(jsonPath);
    ptrJson = model->getList();
    if (!ptrJson)
    {
        QMessageBox::critical(this, QString("Error on write json"), QString("Json in model doesn't exist"));
        return ;
    }
    foreach (SocialTraffic jsonValue, *ptrJson)
        jsonArray << jsonValue.toJSON();
    jsonFile.setArray(jsonArray);
    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        file.write(jsonFile.toJson());
        file.close();
    }
}
