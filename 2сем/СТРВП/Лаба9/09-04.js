const http = require('http');

const data = JSON.stringify({ key: 'value' });

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/json',
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Content-Length': data.length,
    },
};

const req = http.request(options, (res) => {
    res.on('data', (chunk) => {
        console.log(`Статус: ${res.statusCode}`);
        console.log(`Данные: ${chunk}`);
    });
});

req.on('error', (error) => {
    console.error(`Ошибка: ${error.message}`);
});

req.write(data);
req.end();