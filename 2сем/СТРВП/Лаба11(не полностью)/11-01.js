const WebSocket = require('ws');
const fs = require('fs');
const path = require('path');

// Создаем директорию upload, если она не существует
const uploadDir = path.join(__dirname, 'upload');
if (!fs.existsSync(uploadDir)) {
    fs.mkdirSync(uploadDir);
}

const wss = new WebSocket.Server({ port: 4000 });

wss.on('connection', ws => {
    console.log('Клиент подключился');

    ws.on('message', message => {
        // Предполагаем, что клиент отправляет JSON с именем файла и содержимым
        const data = JSON.parse(message);
        const filePath = path.join(uploadDir, data.filename);
        fs.writeFileSync(filePath, data.content, 'utf8');
        console.log(`Файл ${data.filename} сохранен в директории upload`);
        ws.send(`Файл ${data.filename} успешно получен`);
    });

    ws.on('close', () => {
        console.log('Клиент отключился');
    });
});

console.log('WS-сервер запущен на порту 4000');