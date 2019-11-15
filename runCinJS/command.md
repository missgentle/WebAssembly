- ccall    
`emcc cfunc.cc --std=c++11 -o ccall.html -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall,getValue] --post-js post-script-ccall.js`    

- cwrap    
`emcc cfunc.cc --std=c++11 -o cwrap.html -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','getValue'] --post-js post-script-cwrap.js`    
