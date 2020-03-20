//@ts-check
"use strict";

const process = require("process");
const fs = require("fs");
const path = require("path");

var args = /* @type{String[]} */(process.argv);

if (args.length >= 3) {
    var inName = args[2];
    var outName = inName + ".h";

    try {
        // read contents of the file
        const inString = fs.readFileSync(inName, 'UTF-8');
        const baseName = path.basename(inName).split(".")[0];
        // split the contents by new line
        const lines = inString.split(/\r?\n/);
    
        var outFile = fs.createWriteStream(outName);

        outFile.write("const char *" + baseName + "_html =");

        // print all lines
        lines.forEach((line) => {
            outFile.write("\n\"" + line.trim().replace(/\"/g,'\\"') + "\\n\"");
        });
        outFile.write(";\n");
        outFile.close();
    } catch (err) {
        console.error(err);
    }
}
else {
    console.log("Use: html_to_h <infile>");
}
