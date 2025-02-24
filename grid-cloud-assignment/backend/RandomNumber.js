import {client} from "./index.js"


export async function CreateTable() {

    // check if table exists
    let res = await client.query(`
        SELECT EXISTS (
           SELECT 1
           FROM   information_schema.tables 
           WHERE  table_schema = 'public'
           AND    table_name = 'random_numbers' 
           );
        `);
    
    // console.log(JSON.stringify(res));
    // console.log(res.rows[0].exists);
    
    // create table if it does not exist
    if (res.rows[0].exists === false) {
        await client.query(`
            CREATE TABLE random_numbers (
                id_code        serial primary key,
                number         integer NOT NULL);
        `);
    }
    
}

export function AddNumber(number){
    client.query(`INSERT INTO random_numbers(id_code, number) VALUES(default, ${number});`);
}

export async function GetNumbers(){
    return await client.query(`SELECT * from random_numbers;`);
}

export function DeleteAll(){
    client.query(`TRUNCATE random_numbers;`);
}

