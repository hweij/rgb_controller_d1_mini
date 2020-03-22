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
        var buffer = fs.readFileSync(inName, null);

        const baseName = path.basename(inName).split(".")[0];
    
        var outFile = fs.createWriteStream(outName);

        outFile.write("#include <c_types.h>\n");
        outFile.write("uint8_t " + baseName + "_data[] = {");

        // print all lines
        var comma = false;
        for (var b of buffer) {
            if (comma) {
                outFile.write(",");
            }
            else {
                comma = true;
            }
            outFile.write(b.toString());
        }
        outFile.write("};\n");
        outFile.write("const int " + baseName + "_data_length = " + buffer.length + ";\n");
        outFile.close();
    } catch (err) {
        console.error(err);
    }
}
else {
    console.log("Use: image_to_h <infile>");
}
