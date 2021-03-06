// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

let path = require('path');

Object.defineProperty(exports, 'root', {
    get: function() {
        let rootPath = path.resolve(__dirname, '..');
        // Output the path to stdout for cmake/gyp commands.
        process.stdout.write(rootPath);
        return rootPath;
    }
});

Object.defineProperty(exports, 'lib', {
    get: function() {
        let libPath = path.resolve(__dirname, '../bin/' + getLibraryName('napa'));
        // Output the path to stdout for cmake/gyp commands.
        process.stdout.write(libPath);
        return libPath;
    }
});

Object.defineProperty(exports, 'inc', {
    get: function() {
        let incPath = path.resolve(__dirname, '../inc');
        // Output the path to stdout for cmake/gyp commands.
        process.stdout.write(incPath);
        return incPath;
    }
});

// Resolve library name according to platform type.
function getLibraryName(originalName) {
    if (process.platform === "win32") {
        return originalName + '.lib';
    } else if (process.platform === 'darwin') {
        return 'lib' + originalName + '.dylib';
    } else if (process.platform === 'linux') {
        return 'lib' + originalName + '.so';
    } else {
        throw new Error(
            'Failed to resolve the library name of "' + originalName +
            '" because your platform type "' + process.platform +
            '"is not supported by require(\'napajs/build\').paths');
    }
}
