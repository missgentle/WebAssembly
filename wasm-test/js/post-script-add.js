__ATPOSTRUN__.push(function () {
	// ͨ��Emscripten�ڲ���addFunction������������ע��һ�������������ظú����ĺ���ָ��
	var newFuncPtr = Module.addFunction(function (num) {
		console.log(`Hello ${num} from JS!`);
	}, "vi");
	// ֱ�ӵ�����C/C++�����ж����wrapper����
	Module.asm['wrapper'](newFuncPtr);
});