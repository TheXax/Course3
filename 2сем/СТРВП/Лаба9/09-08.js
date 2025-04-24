const http = require('http');

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/get-file',
    method: 'GET',
};

const req = http.request(options, (res) => {
    res.on('data', (chunk) => {
        console.log(`Данные: ${chunk}`);
    });
});

req.on('error', (error) => {
    console.error(`Ошибка: ${error.message}`);
});

req.end();























//insomnia   http://localhost:3000/get-file