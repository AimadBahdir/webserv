const express = require("express");

const app = express();
app.use(express.json());

const mysql = require('mysql2');
const pool = mysql.createPool({
    
    host: "127.0.0.1",
    user: "admin",
    database: "webserv",
    password: "admin"
});

app.use('/', async (req, res) => {
    if (req.method === 'POST') {
        let sql = `INSERT INTO users(username, age) VALUES('${req.query["username"]}', '${req.query["age"]}');`;
        pool.execute(sql, function (err, result) {
            if(err) 
                console.log(err);
            return res.send(result);  
        })
    }
    else if (req.method == 'DELETE')
    {
       let sql = ` DELETE FROM users WHERE username = '${req.query["username"]}';`;
        pool.execute(sql, function (err, result) {
            return res.send(result);  
        })
    }
    else
    {
        let sql = "SELECT * FROM users;"
        pool.execute(sql, function (err, result) {
            return res.send(result);  
        })
        
    }
});

/*
    create database webser;
    CREATE TABLE `users`
    (
    `username`    varchar(250),
    `age` varchar(205)
    );
*/


// Listen on pc port
const PORT = 3000;
app.listen(PORT, () => console.log(`Server running on PORT ${PORT}`));