const moduleName = require('bindings')('module_name')

console.log(moduleName.calc(6.123, 7.456));
moduleName.testCb('test', (test) => {
    console.log(test);
}, { test: 'Hello' });