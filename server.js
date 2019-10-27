// server to respond to a request
const express = require('express');
const http = require('http');
const app = express();
const server = http.createServer(app);

// server will always find an open port
const port = process.env.PORT || 3001;
server.listen(port, '0.0.0.0', () => 
{
    console.log('Server is running on port: ', port);
});

// send content
app.get('/', (req, res) => 
{
    res.sendFile(__dirname + "/public/index.html");
});

app.post('/insertData', (req, res) => 
{
    const params = req.body;
    iceCreams.push(params.flavor);
    res.redirect('/');
});

app.get('/getData', (req, res) => 
{
    res.send(iceCreams.toString());
});