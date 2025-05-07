const RpcServer = require('rpc-websockets').Server;
const readline = require('readline');

const server = new RpcServer({ port: 4000, host: 'localhost' });

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.on('line', input => {
    const event = input.trim().toUpperCase();
    if (['A', 'B', 'C'].includes(event)) {
        server.event(event);
        console.log(`Сгенерировано событие ${event}`);
    } else {
        console.log('Введите A, B или C для генерации события');
    }
});

console.log('WS-сервер запущен на порту 4000. Введите A, B или C для генерации события.');