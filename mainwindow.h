#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>
#include <QMutableLinkedListIterator>
#include <QItemSelectionModel>
#include <trafficitemmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    TrafficItemModel *model;
    QJsonParseError jsonErr;
    QString jsonPath;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addEntry_clicked();

    void on_deleteEntry_clicked();

    void on_changeEntry_clicked();

    void on_readJson_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_writeJson_clicked();

private:
    Ui::MainWindow *ui;
    void addEntry();
    bool readFile();
    void setUIEnabled(bool bEnabled);
    void changeJson(SocialTraffic jObject);
    void clearTextBox();
    bool isExist(int iD);
};
#endif // MAINWINDOW_H
