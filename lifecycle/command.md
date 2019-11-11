- 初始化环境变量    
  `cd D:\SoftWare\emsdk`    
  `emsdk_env.bat`    
  `cd D:\WorkSpace\WebAssembly\test`    

- 在当前目录临时启动一个http服务    
  `python -m SimpleHTTPServer 8081`    
  访问：http://127.0.0.1:8081/lifecycle.html    

- ERE执行生命周期    
  `emcc lifecycle.cc -s WASM=1 -o lifecycle.html --post-js post-script-lifecycle.js -s NO_EXIT_RUNTIME=0`    
