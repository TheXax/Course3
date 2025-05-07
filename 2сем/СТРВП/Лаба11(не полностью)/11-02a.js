const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');
    ws.send('example.txt'); // Запрашиваем файл
});

ws.on('message', message => {
    const data = JSON.parse(message);
    if (data.error) {
        console.log('Ошибка:', data.error);
    } else {
        console.log(`Получен файл ${data.filename}: ${data.content}`);
    }
});

ws.on('close', () => {
    console.log('Соединение закрыто');
});