import express from 'express';
import pg from 'pg';
import {CreateTable, AddNumber, GetNumbers, DeleteAll} from "./RandomNumber.js";
import cors from 'cors';


const app = express();
app.use(express.json());
app.use(cors()) 
const { Client } = pg


const PORT = 5000;
export const client = new Client({
    host: "postgres",
    user: "postgres",
    password: "postgres",
    port: 5432,
    database: "stripe-example"
})

app.post('/post', async (req, res) => {
    
    try {
        const {number} = req.body;
        await AddNumber(number);
        res.json(number);
    } catch (e) {
        res.status(500).json(e);
    }
    
})

app.delete('/delete', async (req, res) => {
    try {
        await DeleteAll();
        res.status(200).json("Deleted all numbers!");
    } catch (e) {
        res.status(500).json(e);
    }

})

app.get('/numbers', async (req, res) => {
    try {
        let table = await GetNumbers();
        res.status(200).json(table.rows);
    } catch (e) {
        res.status(500).json(e);
    }

})

async function startApp(){
    try {
        await client.connect();
        app.listen(PORT, () => console.log('Server is running on port ' + PORT));
        await CreateTable(); 
    }
    catch (err) {console.log(err)}
}


startApp();


