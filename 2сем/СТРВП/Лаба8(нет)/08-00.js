const http = require('http');
const { URL } = require('url');

let keepAliveTimeout = 5000; // Значение по умолчанию

const server = http.createServer((req, res) => {
    const url = new URL(req.url, `http://${req.headers.host}`);
    
    //задание 1
    if (url.pathname === '/connection') {
        if (url.searchParams.has('set')) {
            keepAliveTimeout = parseInt(url.searchParams.get('set'), 10);
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`New value KeepAliveTimeout=${keepAliveTimeout}`);
        } else {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`This value KeepAliveTimeout=${keepAliveTimeout}`);
        }
    }
        
    //задание 2
    if (url.pathname === '/headers') {
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        res.write('Request headers:\n');
        for (const [key, value] of Object.entries(req.headers)) {
            res.write(`${key}: ${value}\n`);
        }
        res.write('\nResponse headlines:\n');
        res.write('X-Custom-Header: MyValue\n');
        res.end();
    }
    
    //задание 3
    if (url.pathname === '/parameter') {
        const x = parseFloat(url.searchParams.get('x'));
        const y = parseFloat(url.searchParams.get('y'));
        
        if (!isNaN(x) && !isNaN(y)) {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`Sum: ${x + y}, Difference: ${x - y}, Multiplication: ${x * y}, Division: ${x / y}`);
        } else {
            res.writeHead(400, { 'Content-Type': 'text/plain' });
            res.end('Error: x and y must be numeric values.');
        }
    }
    
    //задание 4
    if (url.pathname.startsWith('/parameter/')) {
        const params = url.pathname.split('/').slice(2);
        const x = parseFloat(params[0]);
        const y = parseFloat(params[1]);
        
        if (!isNaN(x) && !isNaN(y)) {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`Sum: ${x + y}, Difference: ${x - y}, Multiplication: ${x * y}, Division: ${x / y}`);
        } else {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`URI: ${url.pathname}`);
        }
    }
    
    //задание 5???????????????
    if (url.pathname === '/close') {
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        res.end('The server will close in 10 seconds..');
        setTimeout(() => {
            server.close(() => {
                console.log('Сервер закрыт.');
            });
        }, 10000);
    }
    
    //задание 6
    if (url.pathname === '/socket') {
        const clientAddress = req.socket.remoteAddress;
        const clientPort = req.socket.remotePort;
        const serverAddress = req.socket.localAddress;
        const serverPort = req.socket.localPort;
    
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        res.end(`Client IP address: ${clientAddress}, Client port: ${clientPort}, Server IP address: ${serverAddress}, Server port: ${serverPort}`);
    }
    
    //задание 7
    if (url.pathname === '/req-data') {
        let data = '';
        req.on('data', chunk => {
            data += chunk;
        });
        req.on('end', () => {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`Data received: ${data}`);
        });
    }
    
    //задание 8
    if (url.pathname === '/resp-status') {
        const code = url.searchParams.get('code');
        const message = url.searchParams.get('mess');
    
        res.writeHead(parseInt(code), { 'Content-Type': 'text/plain' });
        res.end(message);
    }
    
    //задание 9
    if (url.pathname === '/') {
        // Отправляем HTML-форму
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(`
            <form action="/formparameter" method="POST">
                <input type="text" name="textInput" placeholder="Text Input">
                <input type="number" name="numberInput" placeholder="Number Input">
                <input type="date" name="dateInput">
                <input type="checkbox" name="checkboxInput" value="checked"> Check me
                <input type="radio" name="radioInput" value="option1"> Option 1
                <input type="radio" name="radioInput" value="option2"> Option 2
                <textarea name="textareaInput" placeholder="Your text here"></textarea>
                <input type="submit" name="submit" value="Submit 1">
                <input type="submit" name="submit" value="Submit 2">
            </form>
        `);
    }

    if (url.pathname === '/formparameter' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            const params = querystring.parse(body);
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(`Received parameters:\n
                Text: ${params.textInput}\n
                Number: ${params.numberInput}\n
                Date: ${params.dateInput}\n
                Checkbox: ${params.checkboxInput ? 'checked' : 'unchecked'}\n
                Radio: ${params.radioInput}\n
                Textarea: ${params.textareaInput}\n
                Submit: ${params.submit}`);
        });
    }

    //задание 10
    if (url.pathname === '/json' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            const parsedData = JSON.parse(body);
            const response = {
                x_plus_y: parsedData.x + parsedData.y,
                Concatination_s_o: parsedData.s + parsedData.o,
                Length_m: parsedData.m.length
            };
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(response));
        });
    }

    //задание 11
    if (url.pathname === '/xml' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            // Парсинг XML и обработка данных
            // Примерный ответ
            const response = `<response><sum value="${sum}"/><concat value="${concat}"/></response>`;
            res.writeHead(200, { 'Content-Type': 'application/xml' });
            res.end(response);
        });
    }

    const fs = require('fs');

    //задание 12
    if (url.pathname === '/files') {
        fs.readdir('./static', (err, files) => {
            if (err) {
                res.writeHead(500);
                return res.end('Ошибка чтения директории');
            }
        res.writeHead(200, { 'X-static-files-count': files.length });
        res.end(`Number of files: ${files.length}`);
        });
    }
    
    //задание 13
    if (url.pathname.startsWith('/files/')) {
        const filename = url.pathname.split('/')[2];
        const filepath = `./static/${filename}`;
        fs.exists(filepath, (exists) => {
            if (exists) {
                res.writeHead(200, { 'Content-Type': 'application/octet-stream' });
                fs.createReadStream(filepath).pipe(res);
            } else {
                res.writeHead(404);
                res.end('File not found');
            }
        });
    }
    
    //задание 14
    if (url.pathname === '/upload') {
        if (req.method === 'GET') {
            res.writeHead(200, { 'Content-Type': 'text/html' });
            res.end('<form action="/upload" method="POST" enctype="multipart/form-data"><input type="file" name="file"><input type="submit" value="Upload"></form>');
        } else if (req.method === 'POST') {
            // Обработка загрузки файла
        }
    }
});

server.listen(5000, () => {
    console.log('Сервер запущен на порту 5000 http://localhost:5000');
});