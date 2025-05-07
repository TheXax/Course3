const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 4000 });

let messageNumber = 0;

wss.on('connection', ws => {
    console.log('Клиент подключился');

    ws.on('message', message => {
        // Парсим полученное сообщение
        const data = JSON.parse(message);
        
        // Логируем информацию о принятом сообщении
        console.log(`Получено сообщение от клиента ${data.client} с меткой времени ${data.timestamp}`);

        // Формируем ответ
        messageNumber++;
        const response = {
            server: messageNumber,
            client: data.client,
            timestamp: data.timestamp
        };
        
        // Отправляем ответ клиенту
        ws.send(JSON.stringify(response));
    });

    ws.on('close', () => {
        console.log('Клиент отключился');
    });
});

console.log('WS-сервер запущен на порту 4000');