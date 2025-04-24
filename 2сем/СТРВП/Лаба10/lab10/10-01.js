const http = require('http');
const fs = require('fs');
const WebSocket = require('ws');

// ====================== HTTP SERVER ======================
const htmlPage = `
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>10-01</title>
</head>
<body>
  <h1>10-01</h1>
  <button onclick="startWS()">startWS</button>
  <div id="log"></div>

  <script>
    let ws;
    let count = 1;
    let intervalId;

    function log(msg) {
      const div = document.getElementById("log");
      div.innerHTML += msg + "<br>";
    } //добавляет сообщение в элемент div с id log

    function startWS() {
      ws = new WebSocket("ws://localhost:4000");

      ws.onmessage = (event) => {
        log("Received: " + event.data);
      };

      ws.onopen = () => {
        log("WebSocket connection opened.");

        intervalId = setInterval(() => {
          ws.send("10-01-client: " + count);
          log("Sent: 10-01-client: " + count);
          count++;
        }, 3000);

        setTimeout(() => {
          clearInterval(intervalId);
          ws.close();
          log("WebSocket connection closed.");
        }, 25000);
      };
    }
  </script>
</body>
</html>
`;

const httpServer = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/start') {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(htmlPage);
  } else {
    res.writeHead(400);
    res.end('Bad Request');
  }
});

httpServer.listen(3000, () => {
  console.log('HTTP сервер запущен на порту 3000');
});

// ====================== WebSocket SERVER ======================
const wsServer = new WebSocket.Server({ port: 4000 });
let wsClientCount = 0;

wsServer.on('connection', (socket) => {
  console.log('Новое WebSocket-соединение');
  let serverMsgCount = 1;
  let lastClientN = 0;

  socket.on('message', (msg) => {
    console.log('Принято от клиента:', msg.toString());
    const match = msg.toString().match(/10-01-client: (\d+)/);
    if (match) lastClientN = parseInt(match[1]);
  });

  const interval = setInterval(() => {
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(`10-01-server: ${lastClientN}->${serverMsgCount++}`);
    }
  }, 5000);

  socket.on('close', () => {
    clearInterval(interval);
    console.log('Клиент отключился');
  });
});

console.log('WebSocket сервер запущен на порту 4000');
