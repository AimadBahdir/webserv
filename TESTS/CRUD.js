const mysql = require('mysql2');
const pool = mysql.createPool({
    host: "127.0.0.1",
    user: "root",
    database: "webserv",
    password: ""
});

if (process.env.REQUEST_METHOD === 'POST')
{
    let sql = `INSERT INTO users(username, age) VALUES('USER1', '15');`;
    pool.execute(sql, function (err, result) {
        if (result.affectedRows > 0)
            console.log("USER1 DELTED SUCCESSFULY");
        pool.end();
     })
}
else if (process.env.REQUEST_METHOD == 'DELETE')
{
    let sql = ` DELETE FROM users WHERE username = 'USER1';`;
    pool.execute(sql, function (err, result) {
        if (result.affectedRows > 0)
            console.log("USER1 INSERTED SUCCESSFULY");
        pool.end();
    });
}
else if (process.env.REQUEST_METHOD == 'GET')
{
    let sql = "SELECT * FROM users;"
    pool.execute(sql, function (err, result) {
        console.log("|\tID\t| USERNAME |\tAGE\t|")
        result.forEach((e) => {
            console.log("-----------------------------"); 
            console.log(`|\t${e.id}\t|\t${e.username}\t|\t${e.age}\t|`); 
        });
        pool.end();
    });
    
}
