const http = require('http');
const fs = require('fs');
const path = require('path');

const server = http.createServer((req, res) => {
    if (req.url === '/functions.wasm') {
        res.writeHead(200, { 'Content-Type': 'application/wasm' });
        fs.createReadStream('functions.wasm').pipe(res);
    } else if (req.url === '/functions.js') {
        res.writeHead(200, { 'Content-Type': 'application/javascript' });
        fs.createReadStream('functions.js').pipe(res);
    } else {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        fs.createReadStream('server.html').pipe(res);
    }
});

server.listen(8080, () => {
    console.log('Сервер запущен на http://localhost:8080');
});