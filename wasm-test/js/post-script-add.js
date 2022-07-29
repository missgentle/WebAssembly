__ATPOSTRUN__.push(function() {
	// 通过Emscripten内部的addFunction向函数索引表中注册一个函数，并返回该函数的函数指针
	var newFuncPtr = Module.addFunction(function(num){
		console.log(`Hello ${num} from JS!`);
	}, "vi");
	// 直接调用在C/C++代码中定义的wrapper函数
	Module.asm['_wrapper'](newFuncPtr);
});
