const express = require('express');
const bodyParser = require('body-parser'); //middleware для обработки тела входящих HTTP-запросов

const app = express();
const PORT = 8080;

//Подключаем middleware body-parser, который позволяет парсить JSON-формат тела запросов
app.use(bodyParser.json());

app.post('/rpc', (req, res) => {
  const { jsonrpc, method, params, id } = req.body; //извлекаем поля из тела запроса

  let result;
  try {
    switch (method) {
      case 'sum':
        //reduce свёртывает (сводит) массив к одному значению, выполняя операцию последовательно на его элементах
        result = params.reduce((a, b) => a + b, 0);
        break;
      case 'mul':
        result = params.reduce((a, b) => a * b, 1);
        break;
      case 'div':
        if (params.length !== 2) throw new Error("Need exactly 2 parameters");
        result = params[0] / params[1];
        break;
      case 'proc':
        if (params.length !== 2) throw new Error("Need exactly 2 parameters");
        result = (params[0] / params[1]) * 100;
        break;
      default:
        throw new Error("Unknown method");
    }

    res.json({ jsonrpc: "2.0", result, id }); //ответ в формате JSON
  } catch (err) {
    res.json({
      jsonrpc: "2.0",
      error: { code: -32602, message: err.message },
      id
    });
  }
});

app.listen(PORT, () => {
  console.log(`JSON-RPC сервер запущен на http://localhost:${PORT}/rpc`);
});
