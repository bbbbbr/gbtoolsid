// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2025

var Module;

Module = {
preRun: [],
postRun: [],
print: (function() {
  return function(text) {
    if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
    // Display text output from program in text area
    // prependInfoText(text + "\n");
    appendInfoText(text + "\n");
  };
})()
};


function invokeProgram(e) {
    let fileBuffer = e.target.result;
    let uint8FileBytes = new Uint8Array(fileBuffer)

    // Print a divider line in output
    appendInfoText("---------------------------------\n");
    let args = [];
    args.push(e.currentTarget.argFilename);
    // console.log(args);

    // Create a file in the virtual file system for passing in the data
    let fileNode = Module['FS_createDataFile'](".", e.currentTarget.argFilename, uint8FileBytes, true, true);

    // Call main() in the program
    callMain(args);

    // Delete the file now that processing is done
    Module['FS_unlink'](e.currentTarget.argFilename);
}
