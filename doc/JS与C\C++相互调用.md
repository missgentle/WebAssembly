> 本文档涉及的所有源代码均摘录自书籍：《深入浅出WebAssembly》，位于 runJSinC/和runCinJS/ 下    

## 在JS代码中调用C/C++函数(runCinJS)    

- Module.ccall(直接调用)    
  `emcc cc/cfunc.cc --std=c++11 -o out/ccall.html -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall,getValue] --post-js js/post-script-ccall.js`

- Module.cwrap(包装函数-除number类型外实际也调用了ccall)    
  `emcc cc/cfunc.cc --std=c++11 -o out/cwrap.html -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','getValue'] --post-js js/post-script-cwrap.js`
   

## 在C/C++代码中调用JS函数(runJSinC)    

### 通过Emscripten内置宏函数    

- emscripten_run_script()    
    `emcc cc/c_run_script.cc -s WASM=1 -o out/c_run_script.html`    

- EM_JS()    
    `emcc cc/em_js.cc -s WASM=1 -o out/em_js.html`

- EM_ASM / EM_ASM_ / EM_ASM_INT / EM_ASM_DOUBLE     
    `emcc cc/em_asm.cc -s WASM=1 -o out/em_asm.html`

### 通过依赖库系统    
  `emcc cc/js_library.cc -s WASM=1 -o out/js_library.html --js-library js/js_library_command.js`    

### 通过函数指针    
  `emcc cc/addfunction.cc --std=c++11 -s WASM=1 -s RESERVED_FUNCTION_POINTERS=20 -s EXTRA_EXPORTED_RUNTIME_METHODS=[addFunction,removeFunction] -o out/addFunction.html --post-js js/post-script-add.js`    
