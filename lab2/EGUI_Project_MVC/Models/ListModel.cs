using System;
using System.Collections.Generic;

namespace EGUI_Project_MVC.Models
{
    public class ListModel
    {
        public ListModel()
        {
            this.listOfRecipes = new List<RecipeModel>();
        }

        public List<RecipeModel> listOfRecipes { get; set; } //this will be the list of recipes
    }
}
