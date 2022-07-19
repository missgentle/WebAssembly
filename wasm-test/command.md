- 初始化环境变量
`d:`    
`cd emsdk`    
`emsdk_env.bat`    
`e:`   
`cd wasm-test`   


- 编译到ASM.js
`emcc hello_emscripten.cc -s ASM_JS=1 -o hello_emscripten.html`

  - node命令运行js
  `node hello_emscripten.js`

  - 另开一个cmd窗口在当前目录临时启动一个http服务
    python2命令:`python -m SimpleHTTPServer 8081`    
    python3命令:`python -m http.server 8081`    
    访问：http://127.0.0.1:8081/hello_emscripten.html    

- 连接C/C++与WebAssembly

  - Standalone类型

    - 使用增强型优化器的方式(Optimizer)
    `emcc cc/emscripten-standalone.cc -Os -s WASM=1 -o out/emscripten-standalone-optimizer.wasm`

    - 在当前目录临时启动一个http服务
    python2命令:`python -m SimpleHTTPServer 8081`
    python3命令:`python -m http.server 8081`

    - http://127.0.0.1:8081/html/index-optimizer.html

    - 编译成动态库的方式(Dynamic Library)
    `emcc cc/emscripten-standalone.cc -s WASM=1 -s SIDE_MODULE=1 -o out/emscripten-standalone-dynamic.wasm`    

    - http://127.0.0.1:8081/html/index-dynamic.html    

    - 反编译wasm(需要emsdk中的命令D:\SoftWare\emsdk\fastcomp\bin\wasm2wat.exe)
    `wasm2wat out/emscripten-standalone-dynamic.wasm -o out/dynamic.wat`    

    `emcc cc/emscripten-standalone.cc -s WASM=1 -s SIDE_MODULE=1 -o out/emscripten-standalone-dynamic.wasm -g4 --source-map-base http://localhost:8081/out/`

  - Dependent类型
  
  `emcc cc/emscripten-dependent.cc -s WASM=1 -s EXPORTED_RUNTIME_METHODS=[ccall] --post-js js/post-script-dependent.js -o out/emscripten-dependent.js`

    - http://127.0.0.1:8081/html/index-dependent.html

- ERE执行生命周期
`emcc cc/lifecycle.cc -s WASM=1 -o out/lifecycle.html --post-js js/post-script-lifecycle.js -s NO_EXIT_RUNTIME=0`

    - http://127.0.0.1:8081/out/lifecycle.html 

- JS中调用C (runCinJS)

  - Module.ccall(直接调用)
  `emcc cc/cfunc.cc --std=c++11 -o out/ccall.html -s WASM=1 -s EXPORTED_RUNTIME_METHODS=[ccall,getValue] --post-js js/post-script-ccall.js`

  - http://127.0.0.1:8081/out/ccall.html

  - Module.cwrap(包装函数-除number类型外实际也调用了ccall)
  `emcc cc/cfunc.cc --std=c++11 -o out/cwrap.html -s WASM=1 -s EXPORTED_RUNTIME_METHODS=[cwrap,getValue] --post-js js/post-script-cwrap.js`

  - http://127.0.0.1:8081/out/cwrap.html 

- C中调用JS (runJSinC)

  - 通过Emscripten内置宏函数
    - emscripten_run_script()
    `emcc cc/c_run_script.cc -s WASM=1 -o out/c_run_script.html`

    - EM_JS()
    `emcc cc/em_js.cc -s WASM=1 -o out/em_js.html`

    - EM_ASM / EM_ASM_ / EM_ASM_INT / EM_ASM_DOUBLE 
    `emcc cc/em_asm.cc -s WASM=1 -o out/em_asm.html`

  - 通过依赖库系统
  `emcc cc/js_library.cc -s WASM=1 -o out/js_library.html --js-library js/js_library_command.js`

  - 通过函数指针
  `emcc cc/addfunction.cc --std=c++11 -s WASM=1 -s RESERVED_FUNCTION_POINTERS=20 -s EXPORTED_RUNTIME_METHODS=[addFunction,removeFunction] -o out/addFunction.html --post-js js/post-script-add.js`

  - http://127.0.0.1:8081/out/addFunction.html

- 快速排序 P61 + 75
`emcc -s WASM=1 -s EXPORTED_RUNTIME_METHODS=[setValue,getValue] -O3 -o out/quicksort.js cc/quicksort.cc`

- 斐波那契数列 P80 + 38
`emcc -s WASM=1 -O3 -o out/fib.js cc/fib.cc`




