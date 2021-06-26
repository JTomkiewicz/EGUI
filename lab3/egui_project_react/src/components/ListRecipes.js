import React, { Component } from 'react';
import axios from 'axios';

export default class ListRecipes extends Component {
    
    //placeholder for recipes
    state = {
        recipes: []
    };

    componentDidMount = () => {
        //call backend for list
        axios.get("/importJSON").then(res => {
            this.setState({
                //set recipes in their place
                recipes: res.data
            });
        });
    };

    //when delete button click, send name of recipe to backend
    deleteRecipe = (nameToDel) => {

        //tell backend to delete recipe with name nameToDel
        axios.post("/deleteRecipe", {}, {
            params: nameToDel
        });

        //reload page
        this.componentDidMount();
        this.render();
    }

    //when edit button click, send name of recipe to backend
    editRecipe = (nameToEdit) => {

        //tell backend to save name of recipe we want to edit
        axios.post("/rememberEditName", {}, {
            params: nameToEdit
        });

        //tell parent to open edit recipe window
        this.props.editRecip();
    }

    render() {
        return (
            <div>

                <div style={{ textAlign: "left", paddingRight: "1%", paddingBottom: "1%", paddingTop: "1%" }}>
                    <button className="btn btn-primary" style={{ marginRight: "3%" }} onClick={this.props.addNew}>Add new recipe</button>
                    <button className="btn btn-primary" onClick={this.props.calcProd}>Calculate products</button>
                </div>

                <p className="display-6" style={{ textAlign: "left" }}>Available recipes:</p>

                <table className="table">
                    <thead className="thead-dark">
                        <tr>
                            <th scope="col" style={{ width: "15%", textAlign: "left" }}>
                                Name
                            </th>
                            <th scope="col" style={{ width: "45%", textAlign: "left" }}>
                                Description
                            </th>
                            <th scope="col" style={{ width: "25%", textAlign: "left" }}>
                                Products
                            </th>
                            <th scope="col" style={{ width: "15%" }}>
                                &nbsp;
                            </th>
                        </tr>
                    </thead>
                    <tbody>
                        {
                            this.state.recipes.map(({ name, recipe, ...products }, i) => (
                                <tr key={`${name}-${i}`}>
                                    <td style={{ textAlign: "left" }}>{name}</td>
                                    <td>
                                        <div>
                                            {!!recipe && recipe.map(line => (
                                                <>
                                                    {line}
                                                    <br />
                                                </>
                                            ))}
                                        </div>
                                    </td>
                                    <td>
                                        {
                                            Object.entries(products).map(([name, desc], i) => (
                                                <div key={`${name}-${desc}-${i}`}>
                                                    {name}: {desc}
                                                </div>
                                            ))
                                        }
                                    </td>
                                    <td style={{ textAlign: "center" }}>
                                        <button 
                                          className="btn btn-primary" 
                                          style={{ width: "70%", marginBottom: "10px" }} 
                                          onClick={() => this.editRecipe(name)}>
                                        Edit
                                        </button>
                                        <button className="btn btn-danger" 
                                          style={{ width: "70%" }} 
                                          onClick={() => this.deleteRecipe(name)}>
                                        Delete
                                        </button>
                                    </td>
                                </tr>
                            )
                            )
                        }
                    </tbody>
                </table>
            </div>
        );
    }
}