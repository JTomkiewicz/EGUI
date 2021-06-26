#ifndef BASKETOFRECIPESVIEW_H
#define BASKETOFRECIPESVIEW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
class BasketOfRecipesView;
}

class BasketOfRecipesView : public QDialog
{
    Q_OBJECT

public:
    explicit BasketOfRecipesView(QWidget *parent = nullptr);
    ~BasketOfRecipesView();

    QList<QJsonObject> listOfObjectsFromJSON;
    QStringList nameOfObjectsFromJSON;

    QStringList chosenRecipes;

    void fillRecipesTable(QStringList names, bool availableTable);
    void calculateProducts();

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnClose_clicked();

private:
    Ui::BasketOfRecipesView *ui;
    QStandardItemModel *model;
};

#endif // BASKETOFRECIPESVIEW_H
