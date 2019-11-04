- 初始化环境变量    
`cd D:\SoftWare\emsdk`    
`emsdk_env.bat`    
`cd D:\WorkSpace\WebAssembly\test`    



- 编译到ASM.js    
`emcc hello_emscripten.cc -s ASM_JS=1 -o hello_emscripten.html`    

  - node命令运行js    
  `node hello_emscripten.js`    

  - 双击html直接运行于浏览器    

- 连接C/C++与WebAssembly    
  - Standalone类型    
    1 使用增强型优化器的方式(Optimizer)    
    `emcc emscripten-standalone.cc -Os -s WASM=1 -o emscripten-standalone-optimizer.wasm`    

     在当前目录临时启动一个http服务    
    `python -m SimpleHTTPServer 8081`    
    访问：http://127.0.0.1:8081/index-optimizer.html    

     wildfly部署：http://127.0.0.1:8080/ux/index-optimizer.html    

    2 编译成动态库的方式(Dynamic Library) ------ ！失败！    
    `emcc emscripten-standalone.cc -s WASM=1 -s SIDE_MODULE=1 -o emscripten-standalone-dynamic.wasm`    

     反编译wasm(需要emsdk中的命令D:\SoftWare\emsdk\fastcomp\bin\wasm2wat.exe)    
    `wasm2wat emscripten-standalone-dynamic.wasm -o dynamic.wat`    

    `emcc emscripten-standalone.cc -s WASM=1 -s SIDE_MODULE=1 -o emscripten-standalone-dynamic.wasm -g4 --source-map-base http://localhost:8081/`    

    > index-dynamic.html:1 Uncaught (in promise) TypeError: WebAssembly.instantiate(): Import #4 module="global" error: module is not an object or function    

     调试方法参考：https://www.itcodemonkey.com/article/3330.html    

  - Dependent类型    
  `emcc emscripten-dependent.cc -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall] --post-js post-script.js -o emscripten-dependent.js`    



