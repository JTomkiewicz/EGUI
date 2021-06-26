#include "basketofrecipesview.h"
#include "ui_basketofrecipesview.h"
#include <QMessageBox>

BasketOfRecipesView::BasketOfRecipesView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasketOfRecipesView)
{
    ui->setupUi(this);
}

BasketOfRecipesView::~BasketOfRecipesView()
{
    delete ui;
}

//fill available recipes table
void BasketOfRecipesView::fillRecipesTable(QStringList names, bool availableTable) {
    //model
    model = new QStandardItemModel(names.length(),1,this);

    //row & col loop
    for(int row = 0; row < names.length(); ++row) {

        //index
        QModelIndex index =  model->index(row,0, QModelIndex());

        //data into index
        model->setData(index,names[row]);

    }

    //if true then insert into available, if false then chosen
    if(availableTable) {
        //insert model into table
        this->ui->tableViewAvailable->setModel(model);

        //column width
        this->ui->tableViewAvailable->setColumnWidth(0,270);
    } else {
        //insert model into table
        this->ui->tableViewChosen->setModel(model);

        //column width
        this->ui->tableViewChosen->setColumnWidth(0,270);
    }

    //set header name
    model->setHeaderData(0,Qt::Horizontal,tr("Name"));

}

//add recipe into chosen recipe
void BasketOfRecipesView::on_btnAdd_clicked()
{
    //new selection model
    QItemSelectionModel *selectionModel = ui->tableViewAvailable->selectionModel();

    //find highlighed rows
    QModelIndexList selectedRows = selectionModel->selectedRows();

    //if more then 1 is highlighted
    if(selectedRows.size() > 1) {

        QMessageBox::critical(this,
                              "Error",
                              "Please select only one row!");
        return;
    } else if(selectedRows.size() == 0) { //no items highlighted

        QMessageBox::critical(this,
                              "No recipe chosen",
                              "Please click on the row item you want to add and then -> button");
        return;
    }

    //take selected row
    QModelIndex selectedRow = selectedRows.takeLast();

    //selected row nr
    int chosenRecipeId = selectedRow.row();

    //name highlighted in selected row
    QString chosenRecipeName = this->nameOfObjectsFromJSON[chosenRecipeId];

    //add chosen recipe to chosen recipe vector
    this->chosenRecipes.push_back(chosenRecipeName);

    //reload table
    this->fillRecipesTable(this->chosenRecipes, false);

    //recalculate needed products
    calculateProducts();
}

//delete from chosen recipes
void BasketOfRecipesView::on_btnDelete_clicked()
{
    //new selection model
    QItemSelectionModel *selectionModel = ui->tableViewChosen->selectionModel();

    //find highlighed rows
    QModelIndexList selectedRows = selectionModel->selectedRows();

    //if more then 1 is highlighted
    if(selectedRows.size() > 1) {

        QMessageBox::critical(this,
                              "Error",
                              "Please select only one row!");
        return;
    } else if(selectedRows.size() == 0) { //no items highlighted

        QMessageBox::critical(this,
                              "No recipe chosen",
                              "Please click on the row index you want to add and then -> button");
        return;
    }

    //take selected row
    QModelIndex selectedRow = selectedRows.takeLast();

    //remove selected recipe from chosen recipes
    this->chosenRecipes.removeAt(selectedRow.row());

    //reload table
    this->fillRecipesTable(this->chosenRecipes, false);

    //recalculate needed products
    calculateProducts();
}

//calculate needed products to cook chosen recipes
void BasketOfRecipesView::calculateProducts() {

    //placeholders for data
    QStringList namesOfProduct;
    QList<double> nrOfProducts;
    QStringList unitsOfProducts;

    for(int i = 0; i < this->chosenRecipes.length(); i++) {

        for(int j = 0; j < this->nameOfObjectsFromJSON.length(); j++) {

            if(this->nameOfObjectsFromJSON[j] == this->chosenRecipes[i]) {
                QStringList keyStrings = this->listOfObjectsFromJSON[j].keys();

                for(int i=0; i < keyStrings.length(); i++) {
                    if(keyStrings[i] != "recipe") {

                        QString nrAndUnit;
                        nrAndUnit = this->listOfObjectsFromJSON[j].value(keyStrings[i]).toString();

                        QStringList nrAndUnitSeparated = nrAndUnit.split(' ');

                        double nrDouble = nrAndUnitSeparated[0].toDouble();
                        QString unitString;

                        for(int k = 1; k < nrAndUnitSeparated.length(); k++) {
                            unitString += nrAndUnitSeparated[k];
                        }

                        bool addNew = true;
                        for(int k = 0; k < namesOfProduct.length(); k++) {
                            if(namesOfProduct[k] == keyStrings[i] && unitString == unitsOfProducts[k]) {

                                nrOfProducts[k] += nrDouble;
                                addNew = false;
                                break;
                            }
                        }

                        //product and unit is new
                        if(addNew) {
                            //push data into lists
                            namesOfProduct.push_back(keyStrings[i]);
                            nrOfProducts.push_back(nrDouble);
                            unitsOfProducts.push_back(unitString);
                        }
                    }
                }
            }
        }

    }

    //placeholder for string that will be inserted
    QString stringIngredientsSum = "";

    for(int i = 0; i < namesOfProduct.length(); i++) {

        //add name
        stringIngredientsSum += namesOfProduct[i];

        //add space
        stringIngredientsSum += " ";

        //add nr and unit
        QString nrString = QString::number(nrOfProducts[i]);;
        stringIngredientsSum += nrString + " " + unitsOfProducts[i];

        //add endline
        stringIngredientsSum += "\n";
    }

    //place string into label
    this->ui->txtNeededIngredients->setPlainText(stringIngredientsSum);
}

//when btn close clicked
void BasketOfRecipesView::on_btnClose_clicked()
{
    this->hide();
}
