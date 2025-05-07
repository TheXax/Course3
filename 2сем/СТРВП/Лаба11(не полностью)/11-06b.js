const RpcClient = require('rpc-websockets').Client;

const ws = new RpcClient('ws://localhost:4000');

ws.on('open', () => {
    console.log('Подключено к серверу');
    ws.subscribe('B');
});

ws.on('B', () => {
    console.log('Событие B произошло');
});