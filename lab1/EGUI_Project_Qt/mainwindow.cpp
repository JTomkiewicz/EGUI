#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "recipeview.h"
#include "basketofrecipesview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //open file
    openJSONFile();

    //file objects into table
    fillTheTable(this->listOfObjectsFromJSON, this->nameOfObjectsFromJSON);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//function to connect and open JSON file
void MainWindow::openJSONFile() {

    //connect to the file
    QFile file("../recipes.json");

    //if file not open close app
    if(!file.open(QIODevice::ReadWrite)) {
       qDebug("File NOT open!");

        //show message in MessageBox
        QMessageBox::critical(this,
                              "Error",
                              "JSON file not open!");
        return;
    }

    //file opened
    qDebug("JSON file opened");

    //create json document
    QJsonDocument recipesJSON = QJsonDocument::fromJson(file.readAll());

    //returns true if document null
    if(!recipesJSON.isNull()) {
        qDebug("JSON file imported successfuly");

        //returns true if document contains object
        if(recipesJSON.isObject()) {
            //take objecy from document
            QJsonObject jsonReceipe = recipesJSON.object();

            //iterator to go throught objects
            QJsonObject::iterator it;

            //placeholders for json object keys and values
            QList<QJsonObject> listOfObjects;
            QStringList nameOfObjects;

            //loop
            for(it = jsonReceipe.begin(); it != jsonReceipe.end(); ++it) {

                //store objects key
                nameOfObjects.push_back(it.key());

                //store object value
                QJsonObject objectInside = it.value().toObject();

                //push objects into list
                listOfObjects.push_back(objectInside);

            }

            //store variables imported from json in program
            this->listOfObjectsFromJSON = listOfObjects;
            this->nameOfObjectsFromJSON = nameOfObjects;

        } else {
            //json file empty
            qDebug("JSON file is empty");
        }
    } else {

    QMessageBox::critical(this,
                          "Error",
                          "JSON file not imported!");
    return;
}

    //close file
    file.close();
}

//when click add new button
void MainWindow::on_btnAdd_clicked()
{
    //new object
    RecipeView *newRV = new RecipeView(this);

    //set title
    newRV->setWindowTitle("New recipe");

    //show
    newRV->show();

    //recipeView needs to know existing elements
    newRV->listOfObjectsFromJSON = this->listOfObjectsFromJSON;
    newRV->nameOfObjectsFromJSON = this->nameOfObjectsFromJSON;

    //true as we are adding, false is for editing
    newRV->boolAddingNew = true;

    //no objecy has 0 products;
    newRV->howManyProducts = 0;

    connect(newRV, SIGNAL(recipeViewCloses()), this, SLOT(reloadMainWindow()));
}

//reaload window when RecipeView closes
void MainWindow::reloadMainWindow() {
    //open file
    openJSONFile();

    //file objects into table
    fillTheTable(this->listOfObjectsFromJSON, this->nameOfObjectsFromJSON);
}

//when click delete button
void MainWindow::on_btnDelete_clicked() {

    //new selection model
    QItemSelectionModel *selectionModel = ui->listOfRecipes->selectionModel();

    //find highlighed rows
    QModelIndexList selectedRows = selectionModel->selectedRows();

    //if more then 1 is highlighted
    if(selectedRows.size() > 1) {

        QMessageBox::critical(this,
                              "Error",
                              "Please select only row!");
        return;
    } else if(selectedRows.size() == 0) { //no items highlighted

        QMessageBox::critical(this,
                              "No recipe chosen",
                              "Please click on the row index you want to delete and then delete button");
        return;
    }

    //take selected row
    QModelIndex selectedRow = selectedRows.takeLast();

    //message box are you sure do delete
    QMessageBox::StandardButton reply =
            QMessageBox::question(this,
                                  "Deleting recipe","Are you sure you want to delete?",
                                  QMessageBox::Yes | QMessageBox::No);

    //if yes delete it
    if(reply == QMessageBox::Yes) {
        qDebug("Yes");

        deleteJsonObject(selectedRow.row());

    } else { //if no nothing happens
        qDebug("No");

    }
}

//load objects into QTableView
void MainWindow::fillTheTable(QList<QJsonObject> array, QStringList names) {

    //new model
    model = new QStandardItemModel(names.length(),3,this);

    //row & col loop
    for(int row = 0; row < names.length(); ++row) {
        for(int col = 0; col < 3; ++col) {

            //index
            QModelIndex index =  model->index(row,col, QModelIndex());

            //take object from list
            QJsonObject object = array[row];

            if(col==0) { //name of object

                model->setData(index,names[row]);

            } else if(col==1) { //recipe

                QJsonArray recipeLines = object.value("recipe").toArray();
                QString stringRecipeToInsert = "";

                for(const auto obj : recipeLines) {
                    stringRecipeToInsert += obj.toString() + "\n";
                }

                model->setData(index,stringRecipeToInsert);

            } else { //ingredients

                QStringList keyStrings = object.keys();
                QString stringIngredientsToInsert = "";

                for(int i=0; i < keyStrings.length(); i++) {
                    if(keyStrings[i] != "recipe") {
                        stringIngredientsToInsert = stringIngredientsToInsert +
                                keyStrings[i] +
                                " " +
                                object.value(keyStrings[i]).toString()+
                                "\n";
                    }
                }

                model->setData(index,stringIngredientsToInsert);

            }
        }
    }

    //set headers
    model->setHeaderData(0,Qt::Horizontal,tr("Name"));
    model->setHeaderData(1,Qt::Horizontal,tr("Recipe"));
    model->setHeaderData(2,Qt::Horizontal,tr("Ingredients"));

    //model into QTableView
    ui->listOfRecipes->setModel(model);

    //columns width
    ui->listOfRecipes->setColumnWidth(0,140);
    ui->listOfRecipes->setColumnWidth(1,370);
    ui->listOfRecipes->setColumnWidth(2,270);

    //word wprapping true
    ui->listOfRecipes->setWordWrap(true);

    //set row height
    QHeaderView* header=ui->listOfRecipes->verticalHeader();
    header->setDefaultSectionSize(250);

}

//remove object from JSON object
void MainWindow::deleteJsonObject(int nrOfRow) {

    //remove object from program vector
    this->listOfObjectsFromJSON.removeAt(nrOfRow);
    this->nameOfObjectsFromJSON.removeAt(nrOfRow);

    //object needed only for delete
    RecipeView *newRVForDelete = new RecipeView(this);

    //recipeView needs to know existing elements
    newRVForDelete->listOfObjectsFromJSON = this->listOfObjectsFromJSON;
    newRVForDelete->nameOfObjectsFromJSON = this->nameOfObjectsFromJSON;

    //save existing JSON objects to file
    newRVForDelete->saveToJson();

    //reload table
    fillTheTable(this->listOfObjectsFromJSON,this->nameOfObjectsFromJSON);
}

//edit existing object
void MainWindow::on_btnEdit_clicked()
{
    //new selection model
    QItemSelectionModel *selectionModel = ui->listOfRecipes->selectionModel();

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
                              "Please click on the row index you want to edit and then Edit button");
        return;
    }

    //take selected row
    QModelIndex selectedRow = selectedRows.takeLast();

    //new object
    RecipeView *editRV = new RecipeView(this);

    //set title
    editRV->setWindowTitle("Edit recipe");

    //show
    editRV->show();

    //recipeView needs to know existing elements
    editRV->listOfObjectsFromJSON = this->listOfObjectsFromJSON;
    editRV->nameOfObjectsFromJSON = this->nameOfObjectsFromJSON;

    //we are NOT adding new, we are editing
    editRV->boolAddingNew = false;

    connect(editRV, SIGNAL(recipeViewCloses()), this, SLOT(reloadMainWindow()));

    //push id of selected row
    editRV->idToEdit = selectedRow.row();

    //highlighted object as new object
    editRV->newObject = this->listOfObjectsFromJSON.takeAt(selectedRow.row());

    //highlighted name as new name
    editRV->newObjectName = this->nameOfObjectsFromJSON.takeAt(selectedRow.row());

    //how many keys have higlighted object
    editRV->howManyProducts = editRV->newObject.keys().size()-1;

    //fill description
    editRV->fillTheDescription();

    //reload table
    editRV->reloadProductTable();
}

void MainWindow::on_actionBasket_of_recipes_triggered()
{
    //new object
    BasketOfRecipesView *newBRP = new BasketOfRecipesView(this);

    //set title
    newBRP->setWindowTitle("Basket of recipes");

    //show
    newBRP->show();

    //BasketOfRecipesView needs to know the objects
    newBRP->listOfObjectsFromJSON = this->listOfObjectsFromJSON;
    newBRP->nameOfObjectsFromJSON = this->nameOfObjectsFromJSON;

    //load table of available recipes
    newBRP->fillRecipesTable(newBRP->nameOfObjectsFromJSON, true);
}

//exit in menu clicked
void MainWindow::on_actionExit_app_triggered()
{
    //exit program
    exit(0);
}
