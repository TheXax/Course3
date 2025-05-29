const express = require('express'); //упрощает создание веб-серверов
const https = require('https');
const fs = require('fs');

const app = express();

// Чтение сертификата и ключа
const options = {
    key: fs.readFileSync('./rs-sva.key'),
    cert: fs.readFileSync('./rs-sva.crt')
};

// Простой GET-обработчик
app.get('/', (req, res) => {
    res.send('Hello, this is a secure HTTPS server for LAB22-SVA!');
});

// Создание HTTPS-сервера
https.createServer(options, app).listen(443, () => {
    console.log('HTTPS server running on port 443');
});