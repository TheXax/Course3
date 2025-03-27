var http = require("http")
var fs = require("fs")
var nodemailer = require("nodemailer")
var Sender = require("./senderData")

var server = http.createServer((request, response) => {
        response.setHeader("Access-Control-Allow-Origin", "*"); //запросы с любого источника
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

            //настройка отправки почты
            let transporter = nodemailer.createTransport({
                service: 'gmail',
                port: 587,
                secure: false,
                auth: {
                    user: Sender.Sender.mail,
                    pass: Sender.Sender.password
                }
            });
        
            //настройки пар-ров письма
            var mailOptions = {
                from: Sender.Sender.mail,
                to: info.to,
                subject: info.subject,
                text: info.message,
                html: `<i>${info.message}</i>`
            };
        
            //отправка письма
            transporter.sendMail(mailOptions, function (error, info) {
                if (error) {
                    console.error(error);
                } else {
                    console.log('Email sent: ' + info.response);
                    response.writeHead(200, {"Content-Type": "text/plain"});
                    response.end("ok")
                }
            });
        })
    }
}).listen(3000, () => console.log('Server running at http://localhost:3000/'))