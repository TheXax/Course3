const http = require('http');
const querystring = require('querystring'); //позволяет сериализовать объекты в формат строковых параметров запроса

const params = querystring.stringify({ x: 5, y: 10 });

const options = {
    hostname: 'localhost',
    port: 3000,
    path: `/get?${params}`,
    method: 'GET',
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

req.end();