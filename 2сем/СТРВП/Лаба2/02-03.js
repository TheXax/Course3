const http = require("http");
  
http.createServer(function(request, response)
{    
    if(request.url === "/api/name" && request.method == 'GET')
    {
        response.setHeader("Content-Type", "text/plain; charset=utf-8;");
        response.end("Strelkovskaya Veronika Andreevna");
    }
    else
    {
        response.setHeader("Content-Type", "text/html; charset=utf-8;");
        response.write("<h2>Not found</h2>");
        response.end();
    }
    
}).listen(5000, function()
        {
            console.log('Сервер успешно запущен http://localhost:5000/api/name');
        }
    );