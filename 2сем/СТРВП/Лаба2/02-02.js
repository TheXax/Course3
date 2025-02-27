const http = require("http");
const fs = require("fs");
  
http.createServer(function(request, response)
{
    const fname = './pic.png'; 
    let png = null;

    if(request.url === "/png")
    {
        fs.stat(fname, (err, stats) => //fs.stat для получения информации о файле
        {
            if(err)
            {
                console.log('error: ', err);
            }
            else
            {
                png = fs.readFileSync(fname);
                response.writeHead(200, {'Content-Type':'image/png', 'Content-Length':stats.size});
                response.end(png, 'binary');
            }
        })
    }
    else
    {
        response.setHeader("Content-Type", "text/html; charset=utf-8;");
        response.write("<h2>Not found</h2>");
        response.end();
    }
    
}).listen(5000, function()
        {
            console.log('Сервер успешно запущен http://localhost:5000/png');
        }
    );