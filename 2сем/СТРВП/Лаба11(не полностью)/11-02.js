const WebSocket = require('ws');
const fs = require('fs');
const path = require('path');

// Создаем директорию download, если она не существует
const downloadDir = path.join(__dirname, 'download');
if (!fs.existsSync(downloadDir)) {
    fs.mkdirSync(downloadDir);
    // Создаем тестовый файл для примера
    fs.writeFileSync(path.join(downloadDir, 'example.txt'), 'Содержимое тестового файла');
}

const wss = new WebSocket.Server({ port: 4000 });

wss.on('connection', ws => {
    console.log('Клиент подключился');

    ws.on('message', message => {
        const filename = message.toString();
        const filePath = path.join(downloadDir, filename);

        if (fs.existsSync(filePath)) {
            const content = fs.readFileSync(filePath, 'utf8');
            const fileData = {
                filename: filename,
                content: content
            };
            ws.send(JSON.stringify(fileData));
        } else {
            ws.send(JSON.stringify({ error: `Файл ${filename} не найден` }));
        }
    });

    ws.on('close', () => {
        console.log('Клиент отключился');
    });
});

console.log('WS-сервер запущен на порту 4000');