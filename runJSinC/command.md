- emscripten_run_script    
  `emcc c_run_script.cc -s WASM=1 -o c_run_script.html`    

- EM_JS    
  `emcc em_js.cc -s WASM=1 -o em_js.html`

- EM_ASM / EM_ASM_ / EM_ASM_INT / EM_ASM_DOUBLE     
    `emcc cc/em_asm.cc -s WASM=1 -o out/em_asm.html`    
