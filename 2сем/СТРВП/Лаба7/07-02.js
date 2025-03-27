var http = require("http")
var fs = require("fs")
var stat = require("./m07-01")("./static")

let http_handler = (req, res) => {
    if(stat.checkMethod(req)!=0) 
        stat.writeHTTPError (res, 405, "wrong method")
    else{
        if(stat.isStatic('html', req.url)) stat.sendFile(req, res, {'Content-Type': 'text/html; charset=utf-8'});
        else if(stat.isStatic('css', req.url)) stat.sendFile(req, res, {'Content-Type': 'text/css; charset=utf-8'});
        else if(stat.isStatic('js', req.url)) stat.sendFile(req, res, {'Content-Type': 'text/javascript; charset=utf-8'});
        else if(stat.isStatic('png', req.url)) stat.sendFile(req, res, {'Content-Type': 'image/png; charset=utf-8'});
        else if(stat.isStatic('docx', req.url)) stat.sendFile(req, res, {'Content-Type': 'application/msword; charset=utf-8'});
        else if(stat.isStatic('json', req.url)) stat.sendFile(req, res, {'Content-Type': 'application/json; charset=utf-8'});
        else if(stat.isStatic('xml', req.url)) stat.sendFile(req, res, {'Content-Type': 'application/xml; charset=utf-8'});
        else if(stat.isStatic('mp4', req.url)) stat.sendFile(req, res, {'Content-Type': 'video/mp4; charset=utf-8'});
        else stat.writeHTTPError(res, 404, 'Resourse not found');
    }
}

let server = http.createServer();
server.on('request', http_handler)
server.listen(3000, () => console.log('Server running at http://localhost:3000/test.html'))
