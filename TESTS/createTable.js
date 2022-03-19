const { Pool, Client } = require('pg')


const client = new Client({
    user: 'admin',
    host: 'localhost',
    database: 'webserv',
    password: '123456',
    port: 5432,
});


const execute = async (query) => {
    try {
        await client.connect();     // gets connection
        await client.query(query);  // sends queries
        return true;
    } catch (error) {
        console.error(error.stack);
        return false;
    } finally {
        await client.end();         // closes connection
    }
};

let text = `
    CREATE TABLE IF NOT EXISTS "users" (
	    "name" VARCHAR(100) NOT NULL
    );`;

execute(text).then(result => {
    if (result) {
        console.log('Table created');
    }
});
