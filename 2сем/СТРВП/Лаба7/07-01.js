var http = require("http")
var fs = require("fs")

let checkMethod = (req) =>{
    if(req.method == "GET") return 0
    else -1
}

// для проверки, соответствует ли запрашиваемый URL формату статического файла с указанным расширением
let isStatic = (ext, fn) => {
    let reg = new RegExp(`^\/.+\.${ext}$`);
    return reg.test(fn);
}

let pathStatic = (fn) => {return `./static${fn}`;} //путь к файлу

//для установления ошибки
let writeHTTPError = (res, code, message) => {
    res.statusCode = code;
    res.statusMessage = message;
    res.end(message);
}

let pipeFile = (req, res, headers) => {
    res.writeHead(200, headers);
    fs.createReadStream(pathStatic(req.url)).pipe(res); //чтение файла
}
 //доступен ли файл
let sendFile = (req, res, headers) => {
    fs.access(pathStatic(req.url), fs.constants.R_OK, err =>{
        if(err) writeHTTPError(res, 404, 'Resourse not found');
        else pipeFile(req, res, headers)
    })
}

//обработка запросов и соответсвтвия файлов
let http_handler = (req, res) => {
    if(checkMethod(req)!=0) 
        writeHTTPError (res, 405, "wrong method")
    else{
        if(isStatic('html', req.url)) sendFile(req, res, {'Content-Type': 'text/html; charset=utf-8'});
        else if(isStatic('css', req.url)) sendFile(req, res, {'Content-Type': 'text/css; charset=utf-8'});
        else if(isStatic('js', req.url)) sendFile(req, res, {'Content-Type': 'text/javascript; charset=utf-8'});
        else if(isStatic('png', req.url)) sendFile(req, res, {'Content-Type': 'image/png; charset=utf-8'});
        else if(isStatic('docx', req.url)) sendFile(req, res, {'Content-Type': 'application/msword; charset=utf-8'});
        else if(isStatic('json', req.url)) sendFile(req, res, {'Content-Type': 'application/json; charset=utf-8'});
        else if(isStatic('xml', req.url)) sendFile(req, res, {'Content-Type': 'application/xml; charset=utf-8'});
        else if(isStatic('mp4', req.url)) sendFile(req, res, {'Content-Type': 'video/mp4; charset=utf-8'});
        else writeHTTPError(res, 404, 'Resourse not found');
    }
}

let server = http.createServer();
server.on('request', http_handler)
server.listen(3000, () => console.log('Server running at http://localhost:3000/test.html'));
