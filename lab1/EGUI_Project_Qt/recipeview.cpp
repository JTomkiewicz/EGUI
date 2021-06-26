#include "recipeview.h"
#include "ui_recipeview.h"
#include <QMessageBox>

RecipeView::RecipeView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeView)
{
    ui->setupUi(this);

}

RecipeView::~RecipeView()
{
    delete ui;
}

//when cancel btn clicked hide the window
void RecipeView::on_btnCancel_clicked()
{
    this->hide();

    emit recipeViewCloses();
}

//when add btn clicked add new recipe to JSON file
void RecipeView::on_btnSave_clicked()
{

    //placeholder for recipe
    QStringList newObjectRecipe;

    //set name
    this->newObjectName = ui->productName->text();

    //recipe separated with newline symbol stored in list
    newObjectRecipe = ui->productDesc->toPlainText().split('\n', QString::SkipEmptyParts);

    //placeholder for recipe in array
    QJsonArray newObjectRecipeArray;
    QJsonValue value;

    //place recipe from list into jsonarray
    for(int i = 0; i < newObjectRecipe.count(); i++) {

        value = newObjectRecipe.at(i);
        newObjectRecipeArray.push_back(value);
    }

    //insert recipe into newObject
    this->newObject.insert("recipe",newObjectRecipeArray);

    if(this->boolAddingNew) { //we are adding object

        //add object and its name to program list of objects
        this->listOfObjectsFromJSON.push_back(this->newObject);
        this->nameOfObjectsFromJSON.push_back(this->newObjectName);

        //save
        this->saveToJson();

        //hide window
        this->hide();

        emit recipeViewCloses();

    } else { //we are editing an existing object

        //remove object at given id
        this->listOfObjectsFromJSON.removeAt(this->idToEdit);
        this->nameOfObjectsFromJSON.removeAt(this->idToEdit);

        //insert objecy at given id
        this->listOfObjectsFromJSON.insert(this->idToEdit,this->newObject);
        this->nameOfObjectsFromJSON.insert(this->idToEdit,this->newObjectName);

        //save
        this->saveToJson();

        //hide window
        this->hide();

        emit recipeViewCloses();

    }

}

//when clicked add button
void RecipeView::on_btnAdd_clicked()
{

    //data inseted into new product
    QString nameOfProduct = this->ui->ingredientName->text();
    QString nrOfProduct = this->ui->ingredientNr->text();
    QString unitOfProduct = this->ui->ingredientUnit->text();

    //name of product cannot be empty
    if(nameOfProduct.trimmed() == "") {
        QMessageBox::critical(this,
                              "Error",
                              "Product name cannot be empty!");
        return;
    }

    //nr of product cannot be empty
    if(nrOfProduct.trimmed() == "") {
        QMessageBox::critical(this,
                              "Error",
                              "Number of product cannot be empty!");
        return;
    }

    //nr of product need to be numerical value
    bool isNum = false;
    bool isInt;
    nrOfProduct.toDouble(&isNum);
    nrOfProduct.toInt(&isInt);
    if(!isNum || isInt) {
        QMessageBox::critical(this,
                              "Error",
                              "Number need to be numeric value!");
        return;
    }

    //unit of product cannot be empty
    if(unitOfProduct.trimmed() == "") {
        QMessageBox::critical(this,
                              "Error",
                              "Unit of product cannot be empty!");
        return;
    }

    //insert into product
    this->newObject.insert(nameOfProduct,nrOfProduct + " " + unitOfProduct);

    //we have 1 more product
    this->howManyProducts++;

    //reload table
    this->reloadProductTable();

    //after adding QPlainText empty
    this->ui->ingredientName->setText("");
    this->ui->ingredientNr->setText("");
    this->ui->ingredientUnit->setText("");
}

//save objects in JSON file
void RecipeView::saveToJson() {

    //new file
    QFile file("../recipes.json");

    //placeholder for products
    QJsonObject projectsInList;

    //loop for every product
    for(int i = 0; i < this->nameOfObjectsFromJSON.size() ; i++)
    projectsInList.insert(nameOfObjectsFromJSON[i], listOfObjectsFromJSON[i]);

    //creates JSON document from object
    QJsonDocument document( projectsInList );

    //if file not open to write
    if( !file.open(QIODevice::WriteOnly) ){
        qDebug("CAN NOT write the file");
        return;
    }

    //overwrite and close
    file.write(document.toJson());
    file.close();
}

//raload product table
void RecipeView::reloadProductTable() {

    //model that will fill the table
    model = new QStandardItemModel(this->howManyProducts,2,this);

    //keys in object
    QStringList keyStrings = this->newObject.keys();

    bool recipeRow = false;

    //row and column loop
    for(int row = 0; row < howManyProducts; ++row) {
        for(int col = 0; col < 2; ++col) {

            QModelIndex index =  model->index(row,col, QModelIndex());

            if(keyStrings[row] == "recipe" || recipeRow == true){
                ++row;
                recipeRow = true;
            }

            if(col==0) { //name of product

                if(keyStrings[row] != "recipe") {
                    model->setData(index,keyStrings[row]);
                }

            } else { //quantity and unit

                //everything except recipe object
                if(keyStrings[row] != "recipe") {

                    //string quantity+unit
                    QString quantityAndUnit = this->newObject.value(keyStrings[row]).toString();

                    //set data in index
                    model->setData(index, quantityAndUnit);
                }

            }

            if(recipeRow){
                --row;
            }
        }
    }

    //set headers of table
    model->setHeaderData(0,Qt::Horizontal,tr("Product name"));
    model->setHeaderData(1,Qt::Horizontal,tr("Quantity and unit"));

    //set model
    this->ui->productView->setModel(model);

    //set width of columns
    this->ui->productView->setColumnWidth(0,260);
    this->ui->productView->setColumnWidth(1,260);
}

void RecipeView::on_btnDelete_clicked()
{
    //new selection model
    QItemSelectionModel *selectionModel = this->ui->productView->selectionModel();

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
                              "No product chosen",
                              "Please click on the row index you want to delete and then Delete button");
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

        //delete product from row selectedRow
        this->deleteProduct(selectedRow.row());

    } else { //if no delete

        qDebug("No");
    }

}

//remove product from JSON object
void RecipeView::deleteProduct(int nrOfRow) {

    //name of product to delte
    QString nameOfProductToDelete = this->model->takeItem(nrOfRow,0)->text();

    //remove key&value from object
    this->newObject.remove(nameOfProductToDelete);

    //products - 1
    this->howManyProducts--;

    //reload table
    this->reloadProductTable();
}

//fill the info about recipe before editing window appear
void RecipeView::fillTheDescription() {

    //set name
    this->ui->productName->setText(this->newObjectName);

    //set recipe
    QJsonArray recipeLines = this->newObject.value("recipe").toArray();

    //string for ingredients
    QString stringRecipeToInsert = "";

    //loop to go throught ingredients
    for(const auto obj : recipeLines) {
        stringRecipeToInsert += obj.toString() + "\n";
    }

    //place ingredients in table
    this->ui->productDesc->setPlainText(stringRecipeToInsert);
}
