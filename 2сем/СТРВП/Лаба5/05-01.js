const http = require('http');
const url = require('url');
const fs = require('fs');
const { DB } = require('./DB'); // Импортируем класс DB
const events = require('events');

const db = new DB();
const stats = {
    startTime: null,
    endTime: null,
    requestCount: 0, //кол-во запросов
    commitCount: 0 //кол-во фиксаций
};

db.on('COMMIT', () => {
    console.log('[COMMIT] Состояние БД зафиксировано');
    stats.commitCount++;
});

// Функция для имитации выполнения команды commit
db.commit = () => {
    db.emit('COMMIT');
};

//для обработки команд из стандартного ввода
const processCommands = () => {
    const stdin = process.stdin;
    stdin.setEncoding('utf8');
    let sdTimeout; //для хранения таймера

    stdin.on('data', (input) => {
        const command = input.trim().split(' ')[0];//пполучаем первый параметр ввода (название функции)
        const param = input.trim().split(' ')[1]; //пар-тр, если есть

        switch (command) {
            case 'sd':
                if (param) {
                    const delay = parseInt(param); //преобразование в целое число
                    if (!isNaN(delay)) {//является ли числом
                        clearTimeout(sdTimeout); //отчистка предыдущего таймера
                        sdTimeout = setTimeout(() => {
                            console.log('Сервер остановлен');
                            process.exit();
                        }, delay * 1000);
                        console.log(`Сервер будет остановлен через ${delay} секунд`);
                    } else {
                        clearTimeout(sdTimeout);
                        console.log('Остановка сервера отменена');
                    }
                } else {
                    clearTimeout(sdTimeout);
                    console.log('Остановка сервера отменена');
                }
                break;

            case 'sc':
                if (param) {
                    const interval = parseInt(param);
                    if (!isNaN(interval)) {
                        db.commitInterval = setInterval(() => {
                            db.commit();
                        }, interval * 1000);
                        console.log(`Периодическая фиксация будет выполняться каждые ${interval} секунд`);
                    }
                } else {
                    clearInterval(db.commitInterval);
                    console.log('Периодическая фиксация остановлена');
                }
                break;

            case 'ss':
                if (param) {
                    const duration = parseInt(param);
                    if (!isNaN(duration)) {
                        stats.startTime = new Date();
                        stats.requestCount = 0;
                        console.log(`Сбор статистики запущен на ${duration} секунд`);
                        setTimeout(() => {
                            stats.endTime = new Date();
                            console.log('Сбор статистики завершен');
                        }, duration * 1000);
                    }
                } else {
                    stats.endTime = new Date();
                    console.log('Сбор статистики остановлен');
                }
                break;

            default:
                console.log('Неизвестная команда');
        }
    });
};

// Обработчики HTTP-запросов
db.on('GET', (req, res) => {
    stats.requestCount++; // Увеличиваем счетчик
    console.log('GET called');
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(db.select());
});

db.on('POST', (req, res) => {
    stats.requestCount++;
    console.log('POST called');
    req.on('data', data => {
        res.writeHead(201, { 'Content-Type': 'application/json' });
        res.end(db.insert(data));
    });
});

db.on('PUT', (req, res) => {
    stats.requestCount++;
    console.log('PUT called');
    req.on('data', data => {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(db.update(data));
    });
});

db.on('DELETE', (req, res) => {
    stats.requestCount++;
    console.log('DELETE called');
    const id = parseInt(url.parse(req.url, true).query.id);
    if (!isNaN(id)) {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(db.delete(id));
    } else {
        res.writeHead(400, { 'Content-Type': 'text/plain' });
        res.end("ERROR! The Id parameter is missing or invalid");
    }
});

http.createServer((req, res) => {
    if (url.parse(req.url).pathname === '/api/db') {
        db.emit(req.method, req, res);
    } else if (url.parse(req.url).pathname === '/api/ss') {
        //stats.requestCount++;
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(stats));
        return;
    } else if (url.parse(req.url).pathname === '/') {
        let html = fs.readFileSync('./04-02.html');
        res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
        res.end(html);
    } else {
        res.writeHead(404, { 'Content-Type': 'text/html' });
        res.end('<html><body><h1>Error! Visit http://localhost:5000/api/db</h1></body></html>');
    }
}).listen(5000, () => {
    console.log('Сервер запущен на http://localhost:5000');
    processCommands();
});