const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000');

let count = 1;
let intervalId;

ws.on('open', () => {
  console.log('WebSocket подключён к серверу');
  
  intervalId = setInterval(() => {
    const msg = `10-01-client: ${count}`;
    ws.send(msg);
    console.log('✔ Отправлено:', msg);
    count++;
  }, 3000);

  setTimeout(() => {
    clearInterval(intervalId);
    ws.close();
    console.log('❌ Соединение закрыто через 25 сек.');
  }, 25000);
});

ws.on('message', (data) => {
  console.log('Ответ от сервера:', data.toString());
});

ws.on('close', () => {
  console.log('Соединение завершено.');
});

ws.on('error', (err) => {
  console.error('❗ Ошибка:', err.message);
});
