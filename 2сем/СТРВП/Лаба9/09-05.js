const http = require('http');

const xmlData = `<data><x>5</x><y>10</y></data>`;

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/xml',
    method: 'POST',
    headers: {
        'Content-Type': 'application/xml',
        'Content-Length': xmlData.length,
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

req.write(xmlData);
req.end();