using System;
using System.Collections.Generic;

namespace EGUI_Project_MVC.Models
{
    public class RecipeModel //this class is a single recipe with description and products
    {
        public RecipeModel()
        {
            this.recipeDesc = new List<string>();
            this.productNames = new List<string>();
            this.productNrUnit = new List<string>();
        }
        
        public string recipeName { get; set; }

        public List<string> recipeDesc { get; set; } //stores description as lines of desc

        //we need to have lists here as we do not know how many products are in a single recipe
        public List<string> productNames { get; set; }

        public List<string> productNrUnit { get; set; }
    }
}