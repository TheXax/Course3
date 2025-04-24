const http = require('http');
const fs = require('fs');
const FormData = require('form-data'); //для работы с формами, позволяя отправлять файлы и другие данные

const form = new FormData();
form.append('file', fs.createReadStream('MyFile.txt'));

const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/upload',
    method: 'POST',
    headers: form.getHeaders(),
};

const req = http.request(options, (res) => {
    res.on('data', (chunk) => {
        console.log(`Данные: ${chunk}`);
    });
});

form.pipe(req);






















//insomnia  http://localhost:3000/upload