var http = require("http")
var fs = require("fs")

function Stat(sfn = "./static"){ //создает объект с методами для работы с HTTP-запросами
    this.FOLDER = sfn
    this.checkMethod = (req) =>{
        if(req.method == "GET") return 0
        else -1
    }
     //соответствует ли запрашиваемый URL формату статического файла с указанным расширением
    this.isStatic = (ext, fn) => {
        let reg = new RegExp(`^\/.+\.${ext}$`);
        return reg.test(fn);
    }
    
    let pathStatic = (fn) => {return `${this.FOLDER}${fn}`;}
    
    this.writeHTTPError = (res, code, message) => {
        res.statusCode = code;
        res.statusMessage = message;
        res.end(message);
    }
    
    //передача файла
    let pipeFile = (req, res, headers) => {
        res.writeHead(200, headers);
        fs.createReadStream(pathStatic(req.url)).pipe(res);
    }
    
    //проверка доступа
    this.sendFile = (req, res, headers) => {
        fs.access(pathStatic(req.url), fs.constants.R_OK, err =>{
            if(err) writeHTTPError(res, 404, 'Resourse not found');
            else pipeFile(req, res, headers)
        })
    }
}

module.exports = (parm)=>{return new Stat(parm)}