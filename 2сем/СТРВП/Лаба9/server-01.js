const http = require('http');

const server = http.createServer((req, res) => {
    if (req.method === 'GET') {
        res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
        res.end('Ответ от сервера');
    }
});

server.listen(3000, () => {
    console.log('Сервер запущен на порту 3000. http://localhost:3000');
});