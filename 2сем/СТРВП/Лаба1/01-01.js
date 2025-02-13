const http =require("http");

http.createServer(function (req, res){
    res.writeHead(200, {'Content-type': 'text/html'})
    res.end("<h1>Hello World</h1>");
}).listen(3000)

console.log('Server running at http://localhost:3000/');