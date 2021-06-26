import { useState } from "react"

const NewProduct = ({ onSubmit }) => {
  const [name, setName] = useState("")
  const [count, setCount] = useState(0)
  const [unit, setUnit] = useState("")

  return (
    <div className="form-group" style={{ marginBottom: "2%" }}>
      <div className="form-row">
        <input
          value={name}
          onChange={({ target }) => setName(target.value)}
          style={{ width: "20%", float: "left", marginRight: "3%" }}
          type="text"
          className="form-control"
          placeholder="Product name"
          id="newProductName"
        />

        <input
          value={count}
          onChange={({ target }) => setCount(parseFloat(target.value))}
          style={{ width: "20%", float: "left", marginRight: "3%" }}
          type="number"
          className="form-control"
          placeholder="Decimal number"
          id="newProductDesc"
          step={0.1}
        />

        <input
          value={unit}
          onChange={({ target }) => setUnit(target.value)}
          style={{ width: "20%", float: "left", marginRight: "3%" }}
          type="text"
          className="form-control"
          placeholder="Unit"
          id="newProductUnit"
        />

        <button
          disabled={!name || !count || !unit}
          style={{ width: "20%" }}
          className="btn btn-secondary"
          onClick={() => !!name && count > 0 && !!unit && onSubmit({ name, count, unit })}
        >Add ingredient</button>
      </div>
    </div>
  )
}

export default NewProduct