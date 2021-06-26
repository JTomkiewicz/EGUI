#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QJsonObject> listOfObjectsFromJSON;
    QStringList nameOfObjectsFromJSON;

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnEdit_clicked();

    void on_actionBasket_of_recipes_triggered();

    void on_actionExit_app_triggered();

public slots:
    void reloadMainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    void openJSONFile();

    void fillTheTable(QList<QJsonObject> array, QStringList names);

    void deleteJsonObject(int nrOfRow);

};
#endif // MAINWINDOW_H
