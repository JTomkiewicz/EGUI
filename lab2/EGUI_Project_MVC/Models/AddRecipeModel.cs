using System;

namespace EGUI_Project_MVC.Models
{
    public class AddRecipeModel
    {
        public RecipeModel recipeToAdd{get;set;}
        public string addProductName {get;set;}
        public string addProductNr {get;set;}
        public string addProductUnit {get;set;}
        public string addRecipeName {get;set;}
        public string addRecipeDesc {get;set;}
    }
}
