import React, { Component } from 'react';

import axios from 'axios';

export default class CalculateProd extends Component {

    //place for available recipes array, chosen recipes array and string that tell sum of ingredients
    state = {
        availRecip: [],
        choseRecip: []
    }

    componentDidMount = () => {
        //call backend for list
        axios.get("/importJSON").then(res => {
            this.setState({
                //set recipes in their place
                availRecip: res.data
            });
        });
    };

    //func that calculated ingredients that are placed in textarea
    calculateSumProducts = (choseRecip) => {

        var namesOfProducts = [];
        var nrOfProducts = [];
        var unitsOfProducts = [];

        var stringIngredientsSum = "";

        //idea of this algorithm is taken from lab2 and lab1 (its exactly the same) only adopted into JS
        choseRecip.forEach(({ name, recipe, ...products }) => {

            Object.entries(products).forEach(([ productName, productDesc ]) => {

                var nrAndUnitSeparated = productDesc.split(' ');

                var numberSeparated = nrAndUnitSeparated[0];
                var unitSeparated = "";

                for(var i = 1; i < nrAndUnitSeparated.length; i++) {
                    unitSeparated += nrAndUnitSeparated[i];
                }

                var addNew = true;

                for(i = 0; i < namesOfProducts.length; i++) {
                    if(namesOfProducts[i] === productName && unitsOfProducts[i] === unitSeparated) {
                        nrOfProducts[i] += parseFloat(numberSeparated);
                        addNew = false;
                        break;
                    }
                }

                if(addNew) {
                    namesOfProducts.push(productName);
                    nrOfProducts.push(parseFloat(numberSeparated));
                    unitsOfProducts.push(unitSeparated);
                }
            })
            console.log("tak")
        })

        for(var i = 0; i < namesOfProducts.length; i++) {
            //add name
            stringIngredientsSum += namesOfProducts[i];

            stringIngredientsSum += " ";

            //add nr
            stringIngredientsSum += nrOfProducts[i];

            stringIngredientsSum += " ";

            //add unit
            stringIngredientsSum += unitsOfProducts[i];

            //add endline
            stringIngredientsSum += "\n";
        }

        return stringIngredientsSum;
    }

    addRecipe = (nameToAdd) => {
        const filtered = this.state.availRecip.filter(({ name }) =>
            name === nameToAdd)
        
        var recipeToAdd = filtered[0];

        this.setState({
            choseRecip: [...this.state.choseRecip, recipeToAdd]
        });
    }

    removeRecipe = (indexToDelete) => {

        var splicedArray = this.state.choseRecip;
        splicedArray.splice(indexToDelete, 1);

        this.setState({
            choseRecip: splicedArray
        });
    }

    render() {
        return(<div>
            <button 
              className="btn btn-primary" 
              onClick={this.props.listRecipes}>
              Back to available recipes
            </button>

            <h2 style={{marginTop: "2%", marginBottom: "2%"}}>Calculate products</h2>

            <div className="form-row">
                <div className="col-5" style={{float: "left", position: "relative", height: "300px", overflow: "auto"}}>
                    <label>Available recipes</label>

                    <table id="availableRecipes" className="table">
                        <thead className="thead-dark">
                            <tr>
                                <th style={{width: "80%"}}>Name</th>
                                <th style={{width: "20%"}}>&nbsp;</th>
                            </tr>
                        </thead>

                        <tbody>
                            {
                                this.state.availRecip.map(({ name, desc }) => (
                                    <tr key={`${name}-${desc}`}>
                                        <td>{name}</td>
                                        <td style={{textAlign: "center"}}>
                                            <button 
                                              className="btn btn-secondary" 
                                              style={{width: "100%"}}
                                              onClick={() => this.addRecipe(name)}>
                                                Add
                                            </button>
                                        </td>
                                    </tr>
                                )
                                )
                            }
                        </tbody>
                    </table>
                </div>

                <div className="col-5" style={{float: "right", position: "relative", height: "300px", overflow: "auto"}}>
                    <label>Chosen recipes</label>

                    <table id="chosenRecipes" className="table">
                        <thead className="thead-dark">
                            <tr>
                                <th style={{width: "80%"}}>Name</th>
                                <th style={{width: "20%"}}>&nbsp;</th>
                            </tr>
                        </thead>

                        <tbody>
                            {
                                this.state.choseRecip.map(({ name }, i) => (
                                    <tr key={`${name}-${i}`}>
                                        <td>{name}</td>
                                        <td style={{textAlign: "center"}}>
                                            <button 
                                              className="btn btn-secondary" 
                                              style={{width: "100%"}}
                                              onClick={() => this.removeRecipe(i)}>
                                                Remove
                                            </button>
                                        </td>
                                    </tr>
                                )
                                )
                            }
                        </tbody>
                    </table>
                </div>

                <div style={{clear: "both"}}></div>
            </div>

            <textarea 
              className="form-control"
              id="sumIngredients"
              rows={ 6 }
              style={{marginTop: "3%", marginLeft: "10%", width: "80%", marginBottom: "3%"}}
              readOnly
              value={this.calculateSumProducts(this.state.choseRecip)}
            />
        </div>);
    }
}