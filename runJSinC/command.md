- 通过Emscripten内置宏函数    
  - emscripten_run_script()    
    `emcc c_run_script.cc -s WASM=1 -o c_run_script.html`    

  - EM_JS()    
    `emcc em_js.cc -s WASM=1 -o em_js.html`    

  - EM_ASM / EM_ASM_ / EM_ASM_INT / EM_ASM_DOUBLE     
    `emcc em_asm.cc -s WASM=1 -o em_asm.html`    

- 通过依赖库系统    
  `emcc js_library.cc -s WASM=1 -o js_library.html --js-library js_library_command.js`    

- 通过函数指针    
  `emcc addFunction.cc --std=c++11 -s WASM=1 -s RESERVED_FUNCTION_POINTERS=20 -s EXTRA_EXPORTED_RUNTIME_METHODS=[addFunction,removeFunction] -o addFunction.html --post-js post-script-add.js`    

