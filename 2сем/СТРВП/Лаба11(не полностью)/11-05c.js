const RpcClient = require('rpc-websockets').Client;

const ws = new RpcClient('ws://localhost:4000');

ws.on('open', async () => {
    console.log('Подключено к серверу');

    const square1 = ws.call('square', [3]);
    const square2 = ws.call('square', [5, 4]);
    const mul1 = ws.call('mul', [3, 5, 7, 9, 11, 13]);
    const fib = ws.call('fib', [7]);
    const mul2 = ws.call('mul', [2, 4, 6]);

    const [s1, s2, m1, f, m2] = await Promise.all([square1, square2, mul1, fib, mul2]);

    const sum = await ws.call('sum', [s1, s2, m1]);
    const fibSum = f.reduce((a, b) => a + b, 0);
    const result = sum + fibSum * m2;

    console.log('Результат выражения:', result);

    ws.close();
});