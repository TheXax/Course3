const fs = require('fs').promises;
const path = require('path');

async function runWasm() {
    try {
        // Чтение WASM-файла
        const wasmBuffer = await fs.readFile(path.join(__dirname, 'functions.wasm'));
        const wasmModule = await WebAssembly.instantiate(wasmBuffer);

        // Извлечение функций
        const { sum, mul, sub } = wasmModule.instance.exports;

        // Тестовые значения
        const x = 10, y = 5;

        // Вызов функций
        console.log(`Сумма (${x}, ${y}): ${sum(x, y)}`);
        console.log(`Умножение (${x}, ${y}): ${mul(x, y)}`);
        console.log(`Вычитание (${x}, ${y}): ${sub(x, y)}`);
    } catch (error) {
        console.error('Ошибка:', error);
    }
}

runWasm();