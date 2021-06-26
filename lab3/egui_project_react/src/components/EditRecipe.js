import React, { Component } from 'react';

import NewProduct from "./NewProduct"
import axios from 'axios';

export default class EditRecipe extends Component {

    //info about recipe
    state = {
        recipeName: "",
        recipeDesc: "",
        products: []
    }

    componentDidMount = () => {
        //import data of recipe to edit
        axios.get("/importRecipeToEdit").then(res => {
            this.setState({
                recipeName: res.data.recipeName,
                recipeDesc: res.data.recipeDesc,
                products: res.data.products
            });
        });
    };

    //name is set to value in input
    setName = (newName) => {
        this.setState({
            recipeName: newName
        });
    }

    //description is set to value in textarea
    setDesc = (newDesc) => {
        this.setState({
            recipeDesc: newDesc
        });
    }

    //when user click save edited recipe
    sendRecipeToBackend = () => {
        //tell backend to add new recipe with following parameters

        //if name empty or only spaces
        if(this.state.recipeName.trim().length === 0 || this.state.recipeName === '') {
            return;
        }

        //if description empty or only spaces
        if(this.state.recipeDesc.trim().length === 0 || this.state.recipeDesc === '') {
            return;
        }

        //if there are no products
        if(this.state.products.length === 0) {
            return;
        }

        //tell backedn to save edited recipe
        axios.post("/saveEditedRecipe", this.state);

        //tell parent to show list of recipes
        this.props.listRecipes();
    }

    deleteProduct = (nameToDel, countToDel, unitToDel) => {
        //list without product to delete
        const filtered = this.state.products.filter(({ name, count, unit }) =>
            name !== nameToDel
            && count !== countToDel
            && unit !== unitToDel)

        this.setState({
            //filtered list in place of old one
            products: filtered
        });
    }

    addNewProduct = (product) => {
        //add new product to the end of products array
        this.setState({
            products: [...this.state.products, product]
        });
    }

    render() {
        return (
            <div style={{ paddingLeft: "10%", paddingRight: "10%" }}>

                <h2>New recipe</h2>

                <div className="form-group" style={{ marginBottom: "2%" }}>
                    <label>Name</label>
                    <input 
                      className="form-control" 
                      type="text"
                      id="newRecipeName"
                      value={this.state.recipeName}
                      onChange={({ target }) => this.setName(target.value)}
                      placeholder={"Insert name"}
                    />
                </div>

                <div className="form-group" style={{ marginBottom: "2%" }}>
                    <label>Description</label>
                    <textarea 
                      className="form-control" 
                      rows={ 6 }
                      id="newRecipeDesc"
                      value={this.state.recipeDesc}
                      onChange={({ target }) => this.setDesc(target.value)}
                      placeholder={"Insert description"}
                    />
                </div>

                <div className="form-group" style={{ marginBottom: "2%" }}>
                    <label>Ingredients</label>

                    <table className="table">
                        <thead className="thead-dark">
                            <tr>
                                <th style={{ width: "30%" }}>
                                    Name
                                </th>

                                <th style={{ width: "30%" }}>
                                    Number
                                </th>

                                <th style={{ width: "30%" }}>
                                    Unit
                                </th>

                                <th style={{ width: "10%" }}>
                                    &nbsp;
                                </th>
                            </tr>
                        </thead>
                        <tbody>
                            {
                                this.state.products.map(({ name, count, unit }) => {
                                    return (
                                        <tr key={`${name}-${count}-${unit}`}>
                                            <td>{name}</td>

                                            <td>{count}</td>

                                            <td>{unit}</td>

                                            <td>
                                                <button 
                                                  className="btn btn-primary" 
                                                  onClick={() => this.deleteProduct(name, count, unit)}>
                                                  Delete
                                                </button>
                                            </td>
                                        </tr>
                                    )
                                })
                            }
                        </tbody>
                    </table>
                </div>

                <NewProduct onSubmit={this.addNewProduct} />

                <button 
                  className="btn btn-primary" 
                  onClick={() => {
                      this.sendRecipeToBackend();
                  }}
                  style={{ marginRight: "1%" }}>
                    Save edited recipe
                </button>

                <button 
                  className="btn btn-danger" 
                  onClick={this.props.listRecipes}>
                  Cancel
                </button>
            </div>
        );
    }
}