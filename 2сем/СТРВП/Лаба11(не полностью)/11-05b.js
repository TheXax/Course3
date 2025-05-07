const RpcClient = require('rpc-websockets').Client;

const ws = new RpcClient('ws://localhost:4000');

ws.on('open', async () => {
    console.log('Подключено к серверу');

    // Параллельные вызовы
    const calls = [
        ws.call('square', [3]),
        ws.call('square', [5, 4]),
        ws.call('sum', [2]),
        ws.call('sum', [2, 4, 6, 8, 10]),
        ws.call('mul', [3]),
        ws.call('mul', [3, 5, 7, 9, 11, 13]),
        ws.call('fib', [1]),
        ws.call('fib', [2]),
        ws.call('fib', [7]),
        ws.call('fact', [0]),
        ws.call('fact', [5]),
        ws.call('fact', [10])
    ];

    const results = await Promise.all(calls);
    console.log('Результаты параллельных вызовов:');
    console.log('square(3):', results[0]);
    console.log('square(5, 4):', results[1]);
    console.log('sum(2):', results[2]);
    console.log('sum(2, 4, 6, 8, 10):', results[3]);
    console.log('mul(3):', results[4]);
    console.log('mul(3, 5, 7, 9, 11, 13):', results[5]);
    console.log('fib(1):', results[6]);
    console.log('fib(2):', results[7]);
    console.log('fib(7):', results[8]);
    console.log('fact(0):', results[9]);
    console.log('fact(5):', results[10]);
    console.log('fact(10):', results[11]);

    ws.close();
});