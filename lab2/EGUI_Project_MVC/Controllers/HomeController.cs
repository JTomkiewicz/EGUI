using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using EGUI_Project_MVC.Models;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace EGUI_Project_MVC.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        //list of json recipes
        public ListModel JSONList = new ListModel();

        //list of json recipes (static)
        public static ListModel JSONBucketList = new ListModel();

        //placeholder for object that will be added
        public static RecipeModel RecipeToAdd = new RecipeModel();

        //string that is placed into checkbox in add recipe view
        public static string descriptionOfNew = "";

        public static int indexOfRecipeToEdit = 0;

        public static bool addMode;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        //controller for index
        public IActionResult Index()
        {
            //just import recipes and show them on page
            importJSON();
            
            return View(JSONList);
        }

        //click calculate products
        public IActionResult CalculateProducts()
        {
            importJSON();
            
            //calculate products needs two models, list from JSON and bucket list
            //so class calculateproductsmodel is needed to simply send two lists to one view
            return View(new CalculateProductsModel(){ jsonList = JSONList, jsonBucketList = JSONBucketList});
        }

        //click NEW recipe
        public IActionResult NewRecipe() 
        {
            addMode = true;
            //recipemodel consists of recipe to add & strings that are placed into insert boxes
            return View(new AddRecipeModel {recipeToAdd = RecipeToAdd, addRecipeDesc=descriptionOfNew});
        }

        //when we click on add new button make sure that all placeholders are clear
        public IActionResult AddThisRecipe()
        {
            descriptionOfNew = "";
            RecipeToAdd.recipeName = "";
            RecipeToAdd.recipeDesc.Clear();
            RecipeToAdd.productNames.Clear();
            RecipeToAdd.productNrUnit.Clear();
            indexOfRecipeToEdit = 0;

            addMode = true;

            return RedirectToAction("NewRecipe");
        }

        //click EDIT recipe
        public IActionResult EditRecipe() 
        {
            addMode = false;

            return View(new AddRecipeModel {recipeToAdd = RecipeToAdd, addRecipeDesc=descriptionOfNew});
        }

        //click EDIT recipe
        public IActionResult EditThisRecipe(string nameToEdit) 
        {
            importJSON();

            int i = 0;
            //delete recipe
            foreach(RecipeModel temp in JSONList.listOfRecipes) 
            {
                //is name to delete is the same as name to delete
                if(temp.recipeName == nameToEdit)
                {
                    
                    RecipeToAdd = JSONList.listOfRecipes[i];

                    string descriptionText = "";

                    for(int j = 0; j < JSONList.listOfRecipes[i].recipeDesc.Count(); j++)
                    {
                        descriptionText += JSONList.listOfRecipes[i].recipeDesc[j];

                        descriptionText += "\n";
                    }

                    descriptionOfNew = descriptionText;

                    indexOfRecipeToEdit = i;

                    addMode = false;

                    break;
                }
                
                i++;
            }

            return RedirectToAction("EditRecipe");
        }


        //click DELETE recipe
        public IActionResult DeleteRecipe(string nameToDelete) 
        {
            importJSON();

            int i = 0;
            //delete recipe
            foreach(RecipeModel temp in JSONList.listOfRecipes) 
            {
                //is name to delete is the same as name to delete
                if(temp.recipeName == nameToDelete)
                {
                    //remove at index i
                    JSONList.listOfRecipes.RemoveAt(i);
                    break;
                }
                i++;
            }
            //save json
            exportJSON(JSONList);

            return RedirectToAction("Index");
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        //import from JSON func
        public void importJSON()
        {
            //open file recipes.json
            string json = System.IO.File.ReadAllText("../recipes.json");

            //parse text from file as object
            JObject allRecipes = JObject.Parse(json);            

            //go throught recipes in allRecipes object
            foreach(JProperty singleRecipe in allRecipes.Properties())
            {
                //recipe model that will be added
                RecipeModel JSONRecipe = new RecipeModel();

                //name of object is easy to set
                JSONRecipe.recipeName = singleRecipe.Name;

                //JToken needs to be prased as JObject
                JObject singleRecipeBody = JObject.Parse(singleRecipe.Value.ToString());

                //go thtought single recipe objects
                foreach(JProperty recipeProperty in singleRecipeBody.Properties()) 
                {
                    //product
                    if(recipeProperty.Name != "recipe")
                    {
                        JSONRecipe.productNames.Add(recipeProperty.Name.ToString());
                        JSONRecipe.productNrUnit.Add(recipeProperty.Value.ToString());
                    }
                    else //recipe text
                    {
                        //this is array so we are parsing to JArray
                        var recipeText = (JArray)recipeProperty.Value;

                        //go throught line of recipeText
                        foreach(var lineOfText in recipeText) 
                        {
                            //add line of text to description
                            JSONRecipe.recipeDesc.Add(lineOfText.ToString());
                        }
                    }
                }

                //add recipe to list
                JSONList.listOfRecipes.Add(JSONRecipe);
            }
        }

        //export to JSON func
        public void exportJSON(ListModel JSONList) 
        {
            //mother object that will be parsed into file
            JObject allRecipesObject = new JObject();

            //we create json objects from recipes and add them to mother
            foreach(RecipeModel temp in JSONList.listOfRecipes) 
            {
                //recipe object placeholder
                JObject recipeObject = new JObject();

                //recipe description will be parsed to JArray
                JArray recipeDescArray = new JArray();

                //recipeDesc List to JArray
                foreach (string lineOfText in temp.recipeDesc)
                {
                    recipeDescArray.Add(lineOfText);
                }

                //add property to JObject
                recipeObject.Add(new JProperty("recipe", recipeDescArray));

                //add products to JObject
                for(int i = 0; i < temp.productNames.Count(); i++)
                {
                    recipeObject.Add(new JProperty(temp.productNames.ElementAt(i), temp.productNrUnit.ElementAt(i)));
                }

                //add recipeObject to allRecipesObject
                allRecipesObject.Add(new JProperty(temp.recipeName, recipeObject));
            }

            //export big object to file
            System.IO.File.WriteAllText("../recipes.json", JsonConvert.SerializeObject(allRecipesObject));
        }

        public IActionResult AddToBusket(string nameToAdd) 
        {
            importJSON();

            foreach(RecipeModel temp in JSONList.listOfRecipes) 
            {
                //look for clicked recipe and add it to bucket list
                if(temp.recipeName == nameToAdd)
                {
                    //add it to list
                    JSONBucketList.listOfRecipes.Add(temp);
                    break;
                }
            }

            return RedirectToAction("CalculateProducts");
        }

        //remove recipes from chosen recipes table
        public IActionResult RemoveFromBucket(string nameToRemove) 
        {
            //needed to find place in list
            int i = 0;

            //loop for recipe to remove from bucket
            foreach(RecipeModel temp in JSONBucketList.listOfRecipes) 
            {
                //look for clicked recipe and add it to bucket list
                if(temp.recipeName == nameToRemove)
                {
                    //remove at index i 
                    JSONBucketList.listOfRecipes.RemoveAt(i);
                    break;
                }
                i++;
            }

            return RedirectToAction("CalculateProducts");
        }

        //func for adding ingredients
        public IActionResult AddProductToNew(AddRecipeModel productsToAdd) 
        {
            if(!String.IsNullOrEmpty(productsToAdd.addProductName)
            && !String.IsNullOrEmpty(productsToAdd.addProductNr)
            && !String.IsNullOrEmpty(productsToAdd.addProductUnit))
            {
                var isDecimal = double.TryParse(productsToAdd.addProductNr, out _);

                //check if product nr string is a decimal nr
                if(isDecimal)
                {
                    //if decimal contains , make it .
                    if(!productsToAdd.addProductNr.Contains(','))
                    {
                        //add ingredients to list
                        RecipeToAdd.productNames.Add(productsToAdd.addProductName);

                        //nr & unit stored together
                        RecipeToAdd.productNrUnit.Add(productsToAdd.addProductNr + " " + productsToAdd.addProductUnit);
                    }
                }
            }
            

            if(addMode) 
            {
                return RedirectToAction("NewRecipe");
            }
            else 
            {
                return RedirectToAction("EditRecipe");
            }
        }

        //func for removing ingredients
        public IActionResult RemoveProductFromNewRecipe(int indexToRemove) 
        {
            //just remove ingredients from end of list
            RecipeToAdd.productNames.RemoveAt(indexToRemove);
            RecipeToAdd.productNrUnit.RemoveAt(indexToRemove);

            if(addMode) 
            {
                return RedirectToAction("NewRecipe");
            }
            else 
            {
                return RedirectToAction("EditRecipe");
            }
        }

        //func to remember name of recipe
        public IActionResult AddNameToNew(AddRecipeModel nameToAdd) 
        {
            if(!String.IsNullOrEmpty(nameToAdd.addRecipeName))
            {
                //add name to new recipe model
                RecipeToAdd.recipeName = nameToAdd.addRecipeName;
            }
            
            if(addMode) 
            {
                return RedirectToAction("NewRecipe");
            }
            else 
            {
                return RedirectToAction("EditRecipe");
            }
        }

        //func responsible for saving recipe description
        public IActionResult AddDescriptionToNew(AddRecipeModel descToAdd) 
        {
            
            RecipeToAdd.recipeDesc.Clear();
            //lines of txt
            if(!String.IsNullOrEmpty(descToAdd.addRecipeDesc))
            {
                string[] descriptionTable = descToAdd.addRecipeDesc.Split('\n');

                //add lines to list
                for(int i = 0; i < descriptionTable.Count(); i++) 
                {
                    RecipeToAdd.recipeDesc.Add(descriptionTable[i]);
                }

                //remember text to display at page reload
                descriptionOfNew = descToAdd.addRecipeDesc;
            }

            if(addMode) 
            {
                return RedirectToAction("NewRecipe");
            }
            else 
            {
                return RedirectToAction("EditRecipe");
            }
            
        }

        //func to add new recipe & save to json
        public IActionResult AddRecipeToJSON() 
        {
            //import objects
            importJSON();

            if(String.IsNullOrEmpty(RecipeToAdd.recipeName) || RecipeToAdd.recipeDesc.Count() == 0) {
                return RedirectToAction("NewRecipe");
            }
            //add new recipe to end of list
            JSONList.listOfRecipes.Add(RecipeToAdd);

            //export new list to json
            exportJSON(JSONList);

            //objects back to default 
            descriptionOfNew = "";
            RecipeToAdd.recipeName = "";
            RecipeToAdd.recipeDesc.Clear();
            RecipeToAdd.productNames.Clear();
            RecipeToAdd.productNrUnit.Clear();

            return RedirectToAction("Index");
        }

        //func to remove old recipe and add new at its place
        public IActionResult SaveEditedRecipe() 
        {
            //import objects
            importJSON();

            JSONList.listOfRecipes.RemoveAt(indexOfRecipeToEdit);
            JSONList.listOfRecipes.Add(RecipeToAdd);

            //export new list to json
            exportJSON(JSONList);

            //objects back to default 
            descriptionOfNew = "";
            RecipeToAdd.recipeName = "";
            RecipeToAdd.recipeDesc.Clear();
            RecipeToAdd.productNames.Clear();
            RecipeToAdd.productNrUnit.Clear();
            indexOfRecipeToEdit = 0;

            addMode = true;

            return RedirectToAction("Index");
        }
    }
}
