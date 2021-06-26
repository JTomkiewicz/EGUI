import './App.css';

import ListRecipes from "./components/ListRecipes"
import NewRecipe from "./components/NewRecipe"
import CalculateProd from "./components/CalculateProd"
import EditRecipe from "./components/EditRecipe"
import { useState } from 'react'

function App() {
  //state that stores info what object to display
  const [state, setState] = useState('list-recipes');

  //show new recipe window
  var triggerNewRecipeState = () => {
    setState('new-recipe');
  }

  //show list recipes window
  var triggerListRecipesState = () => {
    setState('list-recipes');
  }

  //show calculate products window
  var triggerCalcProdState = () => {
    setState('calc-prod');
  }

  //show edit recipe window
  var triggerEditRecipeState = () => {
    setState('edit-recipe');
  }

  return (
    <div className="App">
      
      <h1 style={{textAlign: "center"}} className="display-3">EGUI Recipe planner</h1>

      <div>
        {state === 'list-recipes' && <ListRecipes addNew={triggerNewRecipeState} calcProd={triggerCalcProdState} editRecip={triggerEditRecipeState}/>}
        {state === 'new-recipe' && <NewRecipe listRecipes={triggerListRecipesState}/>}
        {state === 'calc-prod' && <CalculateProd listRecipes={triggerListRecipesState}/>}
        {state === 'edit-recipe' && <EditRecipe listRecipes={triggerListRecipesState}/>}
      </div>

      <footer>
        <p style={{textAlign: "center"}}>Made by Jakub Tomkiewicz</p>
      </footer>
    </div>
  );
}

export default App;
