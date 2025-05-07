const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');
});

ws.on('message', message => {
    console.log('Получено сообщение:', message.toString());
});

ws.on('close', () => {
    console.log('Соединение закрыто');
});