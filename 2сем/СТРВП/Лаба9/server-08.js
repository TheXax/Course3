const http = require('http');
const fs = require('fs');

const server = http.createServer((req, res) => {
    if (req.method === 'GET') {
        const fileStream = fs.createReadStream('MyFile.txt');
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        fileStream.pipe(res);
    }
});

server.listen(3000, () => {
    console.log('Сервер запущен на порту 3000. http://localhost:3000/get-file');
});