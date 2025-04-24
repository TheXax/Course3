// broadcast-client.js
const WebSocket = require('ws');
const readline = require('readline');

const ws = new WebSocket('ws://localhost:5000');

ws.on('open', () => {
  console.log('✅ Подключено к серверу');
  rl.setPrompt('Введите сообщение: ');
  rl.prompt();
});

ws.on('message', (data) => {
  console.log('\n⬅ Получено:', data.toString());
  rl.prompt();
});

ws.on('close', () => {
  console.log('🔚 Соединение закрыто');
  process.exit(0);
});

ws.on('error', (err) => {
  console.error('❗ Ошибка:', err.message);
});

// CLI интерфейс
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.on('line', (input) => {
  ws.send(input);
});
