const WebSocket = require('ws');

const server = new WebSocket.Server({ port: 5000 });
const clients = new Set();

console.log('Broadcast-сервер запущен на порту 5000');

server.on('connection', (ws) => {
  clients.add(ws);
  console.log('Новый клиент подключен');

  ws.on('message', (message) => {
    console.log('Получено сообщение:', message.toString());

    // Рассылка всем клиентам, кроме отправителя
    for (let client of clients) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(`Broadcast: ${message}`);
      }
    }
  });

  ws.on('close', () => {
    clients.delete(ws);
    console.log('❌ Клиент отключён');
  });
});
