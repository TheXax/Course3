const http = require('http');

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/get',
    method: 'GET',
};

const req = http.request(options, (res) => {
    console.log(`Статус: ${res.statusCode}`);
    console.log(`Сообщение: ${res.statusMessage}`);
    console.log(`IP-адрес: ${options.hostname}`);
    console.log(`Порт: ${options.port}`);

    res.on('data', (chunk) => {
        console.log(`Данные: ${chunk}`);
    });
});

req.on('error', (error) => {
    console.error(`Ошибка: ${error.message}`);
});

req.end();