const WebSocket = require('ws');

// Получаем имя клиента из аргумента командной строки
const clientName = process.argv[2] || 'Клиент1';

const ws = new WebSocket('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');
    const message = {
        client: clientName,
        timestamp: new Date().toISOString()
    };
    ws.send(JSON.stringify(message));
});

ws.on('message', message => {
    console.log('Ответ от сервера:', message.toString());
});

ws.on('close', () => {
    console.log('Соединение закрыто');
});