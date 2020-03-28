//@ts-check
"use strict";

const fs = require("fs");
const path = require("path");

const http = require('http'); 

const server = http.createServer(function (req, res) {   
    if (req.url.startsWith('/api/set')) {
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.write(JSON.stringify({ result:"OK", r:0, g:0, b:0 }));  
            res.end();  
    }
    else {
        // No match: serve the file
        serveStatic(res, req.url);
        // if (req.url === '/') {
        //     // Web root, server index page
        //     serveFile(res, "text/html", "controller.html");
        // }
    }
});

server.listen(8080);

console.log('Node.js web server at port 8080 is running..');

function serveStatic(res, url) {
    // Special case for index files
    if (url.endsWith("/")) {
        url += "index.html";
    }
    const fpath = "./data" + url;
    console.log(fpath);
    if (fs.existsSync(fpath)) {
        // Deduct mime type from extension
        const ext = path.extname(url);
        console.log("Extension = " + ext);
        var mime = "text/plain";
        switch (ext) {
            case ".html":
            case ".htm":
                mime = "text/html";
                break;
            case ".json":
                mime = "application/json";
                break;
            case ".png":
                mime = "image/png";
                break;
            case ".ico":
                mime = "image/x-icon";
                break;
        }
        serveFile(res, mime, fpath);
    }
}

function serveFile(res, mime, fname) {
    res.writeHead(200, { 'Content-Type': mime });
    var content = fs.readFileSync(fname);
    res.write(content);
    res.end();
}