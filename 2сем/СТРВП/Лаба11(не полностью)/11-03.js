const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 4000 });

let messageNumber = 0;

// Отправка сообщений каждые 15 секунд
setInterval(() => {
    messageNumber++;
    const message = `11-03-server: ${messageNumber}`;
    wss.clients.forEach(client => {
        if (client.isAlive) {
            client.send(message);
        }
    });
}, 15000);

// Проверка соединений через ping/pong каждые 5 секунд
setInterval(() => {
    let aliveClients = 0;
    wss.clients.forEach(client => {
        if (client.isAlive === false) return client.terminate();

        client.isAlive = false;
        client.ping();
        aliveClients++;
    });
    console.log(`Количество работоспособных соединений: ${aliveClients}`);
}, 5000);

wss.on('connection', ws => {
    console.log('Клиент подключился');
    ws.isAlive = true;

    ws.on('pong', () => {
        ws.isAlive = true;
    });

    ws.on('close', () => {
        console.log('Клиент отключился');
    });
});

console.log('WS-сервер запущен на порту 4000');