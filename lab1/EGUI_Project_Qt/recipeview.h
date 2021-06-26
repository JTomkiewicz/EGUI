#ifndef RECIPEVIEW_H
#define RECIPEVIEW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
class RecipeView;
}

class RecipeView : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeView(QWidget *parent = nullptr);
    ~RecipeView();

    QList<QJsonObject> listOfObjectsFromJSON;
    QStringList nameOfObjectsFromJSON;

    bool boolAddingNew;
    int idToEdit;

    void saveToJson();

    void reloadProductTable();

    QJsonObject newObject;
    QString newObjectName;
    int howManyProducts;

    void deleteProduct(int nrOfRow);

    void fillTheDescription();

signals:
   void recipeViewCloses();

private slots:
    void on_btnCancel_clicked();

    void on_btnSave_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

private:
    Ui::RecipeView *ui;
    QStandardItemModel *model;
};

#endif // RECIPEVIEW_H
