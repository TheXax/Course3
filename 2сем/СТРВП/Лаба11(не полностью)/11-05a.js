const RpcClient = require('rpc-websockets').Client;

const ws = new RpcClient('ws://localhost:4000');

ws.on('open', async () => {
    console.log('Подключено к серверу');

    // Обертываем каждый вызов в try-catch для обработки ошибок
    try {
        console.log('square(3):', await ws.call('square', [3]));
    } catch (error) {
        console.error('Ошибка при вызове square(3):', error.message);
    }

    try {
        console.log('square(5, 4):', await ws.call('square', [5, 4]));
    } catch (error) {
        console.error('Ошибка при вызове square(5, 4):', error.message);
    }

    try {
        console.log('sum(2):', await ws.call('sum', [2]));
    } catch (error) {
        console.error('Ошибка при вызове sum(2):', error.message);
    }

    try {
        console.log('sum(2, 4, 6, 8, 10):', await ws.call('sum', [2, 4, 6, 8, 10]));
    } catch (error) {
        console.error('Ошибка при вызове sum(2, 4, 6, 8, 10):', error.message);
    }

    try {
        console.log('mul(3):', await ws.call('mul', [3]));
    } catch (error) {
        console.error('Ошибка при вызове mul(3):', error.message);
    }

    try {
        console.log('mul(3, 5, 7, 9, 11, 13):', await ws.call('mul', [3, 5, 7, 9, 11, 13]));
    } catch (error) {
        console.error('Ошибка при вызове mul(3, 5, 7, 9, 11, 13):', error.message);
    }

    try {
        console.log('fib(1):', await ws.call('fib', [1]));
    } catch (error) {
        console.error('Ошибка при вызове fib(1):', error.message);
    }

    try {
        console.log('fib(2):', await ws.call('fib', [2]));
    } catch (error) {
        console.error('Ошибка при вызове fib(2):', error.message);
    }

    try {
        console.log('fib(7):', await ws.call('fib', [7]));
    } catch (error) {
        console.error('Ошибка при вызове fib(7):', error.message);
    }

    try {
        console.log('fact(0):', await ws.call('fact', [0]));
    } catch (error) {
        console.error('Ошибка при вызове fact(0):', error.message);
    }

    try {
        console.log('fact(5):', await ws.call('fact', [5]));
    } catch (error) {
        console.error('Ошибка при вызове fact(5):', error.message);
    }

    try {
        console.log('fact(10):', await ws.call('fact', [10]));
    } catch (error) {
        console.error('Ошибка при вызове fact(10):', error.message);
    }

    ws.close();
});