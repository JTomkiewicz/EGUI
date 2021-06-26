const express = require('express');
const bp = require('body-parser');
const app = express();
const port = 5000;
const fs = require('fs');

app.use(bp.json())
app.use(bp.urlencoded({ extended: true }))

//function to read from json with formating (name is in object, not as key)
function importJSON() {
    //read file (nothing more untill is read)
    let jsonData = fs.readFileSync('recipes.json');
    let listOfRecipes = JSON.parse(jsonData);

    //placeholder for recipes
    var recipesToExport = [];

    for(var [key, value] of Object.entries(listOfRecipes)) {
        
        var recipe = new Object();
        
        //put name inside object
        recipe["name"] = key;

        //rest of object the same
        for(var [key2, value2] of Object.entries(value)) {
            recipe[key2] = value2;
        }

        //add object to recipes
        recipesToExport.push(recipe);
    }

    //export
    return recipesToExport;
}

//function to read json without formating data
function importJSONwithoutFormat() {

    //just read data from file
    let jsonData = fs.readFileSync('recipes.json');
    let listOfRecipes = JSON.parse(jsonData);

    //and export
    return listOfRecipes;
}

//function to write to json
function exportJSON(listOfRecipes) {
    //stringify
    let jsonData = JSON.stringify(listOfRecipes);

    //write
    fs.writeFileSync('recipes.json', jsonData);
}

//when server on show it in terminal
app.listen(port, () => console.log("Backend is listening"));

//when react call, send him objects
app.get("/importJSON", (req, res) => res.send(importJSON()));

//frontend wants to delete a recipe
app.post("/deleteRecipe", (req, res) => {

    //read json
    var listOfRecipes = importJSONwithoutFormat();

    //locate the object to delete
    for(var [key, value] of Object.entries(listOfRecipes)) {
        
        if(key === req.query[0]) { //object found
            delete listOfRecipes[key];
        }
    }

    //write new list to json
    exportJSON(listOfRecipes);
});

//when frontend wants to add new recipe
app.post("/addNewRecipe", (req, res) => {

    //elements that will be added
    let nameToAdd = req.body.recipeName;
    let descToAdd = req.body.recipeDesc;
    let { products } = req.body;

    //recipe desc into array
    let recipe = {
        recipe: descToAdd.split('\n')
    }

    //products into json readable form
    for (const { name, count, unit } of products) {
        recipe = {
            ...recipe,
            [name]: `${count} ${unit}`
        }
    }

    //read json
    var listOfRecipes = importJSONwithoutFormat();

    var unique = true;

    //no posibility to add recipe if exist with such name
    for(var [key, value] of Object.entries(listOfRecipes)) {
        if(key === nameToAdd) {
            unique = false;
        }
    }

    if(unique) {
        //add new recipe at the end
        listOfRecipes[nameToAdd] = recipe;

        //write new list to json
        exportJSON(listOfRecipes);
    }
    
});

//this will be the name of recipe that will be edited 
var nameToEdit = "";

//frontend wants to delete a recipe
app.post("/rememberEditName", (req, res) => {

    nameToEdit = req.query[0];
});

//returns object that frontend wants to edit (having its name)
function importRecipeToEdit() {
    
    //info about recipe
    var recipeToSend = {
        recipeName: "",
        recipeDesc: "",
        products: []
    }

    //read json
    var listOfRecipes = importJSON();

    //go through recipes
    listOfRecipes.map(({ name, recipe, ...products }) => {

        //recipe that we are looking for
        if(name === nameToEdit) {

            //recipe needs to be as string (not array or txt lines)
            var recipeInOneString = "";

            for(var i = 0; i < recipe.length; i++) {
                recipeInOneString += recipe[i];

                recipeInOneString += "\n";
            }

            //products must be parsed into react object readable form
            Object.entries(products).map(([ productName, productDesc ]) => {
                var nrAndUnitSeparated = productDesc.split(' ');

                var numberSeparated = nrAndUnitSeparated[0];
                var unitSeparated = "";

                for(var i = 1; i < nrAndUnitSeparated.length; i++) {
                    unitSeparated += nrAndUnitSeparated[i];
                }

                var productToPush = {
                    name: productName,
                    count: numberSeparated,
                    unit: unitSeparated
                }

                //add product to products array
                recipeToSend.products.push(productToPush);
            })

            //add name and recipe desc to object
            recipeToSend.recipeName = name;
            recipeToSend.recipeDesc = recipeInOneString;
        }
    })

    //return object
    return recipeToSend;
}

//when frontend wants to edit a recipe send him object
app.get("/importRecipeToEdit", (req, res) => res.send(importRecipeToEdit()));

//when frontend wants to save exited recipe
app.post("/saveEditedRecipe", (req, res) => {

    //import objects
    var listOfRecipes = importJSONwithoutFormat();

    //locate the object to delete
    for(var [key, value] of Object.entries(listOfRecipes)) {
        
        if(key === nameToEdit) { //object found
            delete listOfRecipes[key];
        }
    }

    //write new list to json
    exportJSON(listOfRecipes);

    //elements that will be added
    let nameToAdd = req.body.recipeName;
    let descToAdd = req.body.recipeDesc;
    let { products } = req.body;

    //split description into array
    let recipe = {
        recipe: descToAdd.split('\n')
    }

    //parse products into json form
    for (const { name, count, unit } of products) {
        recipe = {
            ...recipe,
            [name]: `${count} ${unit}`
        }
    }

    //read json (without earlier deleted object)
    listOfRecipes = importJSONwithoutFormat();

    var unique = true;

    //no posibility to add recipe if exist with such name
    for(var [key, value] of Object.entries(listOfRecipes)) {
        if(key === nameToAdd) {
            unique = false;
        }
    }

    if(unique) {
        //add new recipe at the end
        listOfRecipes[nameToAdd] = recipe;

        //write new list to json
        exportJSON(listOfRecipes);
    }
   
});