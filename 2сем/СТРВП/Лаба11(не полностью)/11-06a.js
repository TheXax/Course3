const RpcClient = require('rpc-websockets').Client;

const ws = new RpcClient('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');
    ws.subscribe('A');
});

ws.on('A', () => {
    console.log('Событие A произошло');
});