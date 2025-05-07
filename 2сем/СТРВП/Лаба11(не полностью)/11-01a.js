const WebSocket = require('ws');
const fs = require('fs');

const ws = new WebSocket('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');

    // Пример отправки файла
    const fileContent = 'Пример содержимого файла';
    const fileData = {
        filename: 'test.txt',
        content: fileContent
    };

    ws.send(JSON.stringify(fileData));
});

ws.on('message', message => {
    console.log('Ответ от сервера:', message.toString());
});

ws.on('close', () => {
    console.log('Соединение закрыто');
});