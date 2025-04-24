const http = require('http');

const data = JSON.stringify({ x: 5, y: 10, s: 'test' });

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/post',
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Content-Length': data.length,
    },
};

const req = http.request(options, (res) => {
    res.on('data', (chunk) => {
        console.log(`Статус: ${res.statusCode}`);
        console.log(`${chunk}`);
    });
});

req.on('error', (error) => {
    console.error(`Ошибка: ${error.message}`);
});

req.write(data);
req.end();