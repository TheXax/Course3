const http = require('http');

const server = http.createServer((req, res) => {
    if (req.method === 'POST') {
        let body = '';
        req.on('data', (chunk) => {
            body += chunk.toString();
        });
        req.on('end', () => {
            res.writeHead(200, { 'Content-Type': 'application/xml' });
            res.end(`<response>${body}</response>`);
        });
    }
});

server.listen(3000, () => {
    console.log('Сервер запущен на порту 3000. http://localhost:3000/xml');
});