> 本文档涉及的所有源代码均摘录自书籍：《深入浅出WebAssembly》，位于 runJSinC/和runCinJS/ 下    

## 在JS代码中调用C/C++函数(runCinJS)    

在构建WebAssembly应用时，一个最常见的需求就是希望能够在JS中调用C/C++源码中暴露出的函数。我们可以借助ERE内部已经封装好的ccall和swrap实现。

- Module.ccall(ident, returnType, argTypes, args)    

第一个参数：一个字符串指定待调用的从wasm模块中导出的函数的函数名。    
第二个参数：一个字符串指定返回值类型。ERE可以使用的返回值类型有四种：number，string，boolean，array，但这个参数却不能指定为'array'，当希望得到array类型的返回值时，这里要指定为'number'返回数组的首地址指针，并通过ERE的Module.getValue()函数从模块的线性内存中提取数据。    
第三个参数：一个数组指定待调用的C/C++函数可接收的参数值类型。    
第四个参数：一个数组指定实际参数值。这里传入的实参类型要与第三个参数指定的对应参数值类型相符。    

该方法内部实现细节：    
第一步：根据第一个参数从wasm模块中导出C/C++函数实体(导出的函数名是带_前缀的，但第一个参数就是真实的函数名)；    
第二步：根据第三个参数指定的形参类型将传入的实参(第四个参数)使用内部对应的toC()方法转换成C/C++可用的数据类型；
第三步：调用模块导出的方法；
第四部：根据第四个参数指定的返回值类型将得到的结果转换成相应的JS数据类型。
比如对于布尔型，将C/C++函数返回的0或1转换为true或false；
对于字符串类型，则需要通过内部方法Pointer_stringify从wasm模块的共享线性内存中提取相应数据(字符串在C中实际是以数组形式存在)。

这里的第二步与第四步，对于相同的数据类型可以看作是一个互逆的过程。

- Module.cwrap(包装函数-除number类型外实际也调用了ccall)    
   

## 在C/C++代码中调用JS函数(runJSinC)    

### 通过Emscripten内置宏函数    

- emscripten_run_script()    

- EM_JS()    

- EM_ASM / EM_ASM_ / EM_ASM_INT / EM_ASM_DOUBLE     

### 通过依赖库系统     

### 通过函数指针    
