import React from 'react'
import "./App.css"
import axios from "axios";

function App() {
    
    
    async function fetchNumbers(){
        const res = await axios.get('http://localhost:5000/numbers')
        console.log("Numbers: " + JSON.stringify(res.data))
    }

    let randomNumber = 4;
    async function addNumber(){
        randomNumber = Math.floor(Math.random() * 100);
        const data = {number: randomNumber};
        const res = await axios.post('http://localhost:5000/post', data)
        console.log(res.data)
    }
    
    async function deleteAllNumbers(){
        const res = await axios.delete('http://localhost:5000/delete')
        console.log(res.data)
    }
  
  
  return (
      <div className="App">
        <div className="container">
          <h1>
            Random number generator
          </h1>
            <div className="btn-container">
                <button className="btn" onClick={fetchNumbers}>get numbers</button>
                <button className="btn" onClick={addNumber}>random</button>
                <button className="btn" onClick={deleteAllNumbers}>reset</button>
            </div>
        </div>
      </div>
  );
}

export default App;
