const http = require('http');
const url = require('url');

const server = http.createServer((req, res) => {
    if (req.method === 'GET') {
        const query = url.parse(req.url, true).query;
        res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
        res.end(`Полученные параметры: x=${query.x}, y=${query.y}`);
    }
});

server.listen(3000, () => {
    console.log('Сервер запущен на порту 3000. http://localhost:3000/get?x=5&y=10');
});