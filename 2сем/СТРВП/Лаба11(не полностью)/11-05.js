const RpcServer = require('rpc-websockets').Server;

const server = new RpcServer({ port: 4000, host: 'localhost' });

// Регистрация RPC-методов
server.register('square', params => {
    if (params.length === 1) {
        return Math.PI * params[0] * params[0]; // Площадь круга
    } else if (params.length === 2) {
        return params[0] * params[1]; // Площадь прямоугольника
    }
}).public();

server.register('sum', params => {
    return params.reduce((a, b) => a + b, 0);
}).public();

server.register('mul', params => {
    return params.reduce((a, b) => a * b, 1);
}).public();

server.register('fib', params => {
    const n = params[0];
    const fib = [0, 1];
    for (let i = 2; i < n; i++) {
        fib.push(fib[i - 1] + fib[i - 2]);
    }
    return fib.slice(0, n);
}).public(); // Временно делаем публичным

server.register('fact', params => {
    const n = params[0];
    let result = 1;
    for (let i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}).public(); // Временно делаем публичным

console.log('RPC WS-сервер запущен на порту 4000');