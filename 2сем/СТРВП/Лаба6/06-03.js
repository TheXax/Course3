var http = require("http")
var fs = require("fs")
var Sender = require("./senderData")
var send = require("./m0603")

var server = http.createServer((request, response) => {
    response.setHeader("Access-Control-Allow-Origin", "*");
        response.setHeader("Access-Control-Allow-Methods", "*");
        response.setHeader("Access-Control-Allow-Headers", "content-type");
        response.setHeader('Access-Control-Allow-Origin', '*');
        response.setHeader('Access-Control-Allow-Headers', 'origin, content-type, accept');
    let path = request.url
    if(path == "/"){
        let page = fs.readFileSync("index.html");
        response.writeHead(200, {"Content-Type": "text/html"});
        response.end(page)
    }
    if(path == "/send"){
        request.on("data", data =>{
            let info = JSON.parse(data)
            console.log(info)

            send.Send(Sender.Sender, info.message)

            response.writeHead(200, {"Content-Type": "text/plain"});
            response.end("ok")
        })
    }
}).listen(3000, () => console.log('Server running at http://localhost:3000/'))