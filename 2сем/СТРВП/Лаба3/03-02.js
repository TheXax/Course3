var http = require('http');
var url = require('url');
const route = 'fact'; //Определяем маршрут, который будет обрабатывать запросы.


var factorial = (x) => 
{
    if (x < 0)
        return "Invalid value!";
    else if (x == 0 || x == 1) 
        return 1; 
    else 
        return x * factorial(x - 1);
};


http.createServer((request, response) => {

    var rc = JSON.stringify({ k: 0 }); //начальное значение rc
    if (url.parse(request.url).pathname === '/' + route && typeof url.parse(request.url, true).query.k != 'undefined') 
    {
        var k = parseInt(url.parse(request.url, true).query.k); 
        if (Number.isInteger(k))
        {
            console.log(k);
            response.writeHead(200, {'Content-Type': 'application/json; charset=utf-8'});
            response.end(JSON.stringify({ k: k, fact: factorial(k) }));
        }
    }
    else 
        response.end(rc);
}).listen(5000, () => console.log('Server running at http://localhost:5000/' + route));
//http://localhost:5000/fact?k=3 