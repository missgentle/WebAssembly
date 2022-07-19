__ATPOSTRUN__.push(() => {
	// 调用Module全局对象上的ccall方法
	const sqrtResult = Module.ccall('doubleSqrt', 'number', ['number'], [400]);
	console.log(sqrtResult);

	const capitalResult = Module.ccall('capitalize', 'string', ['string'], ["yhapy111"]);
	console.log(capitalResult);

	// 由于ccall并不支持array返回值类型，所以这一步返回了number类型的新数组首地址
	let arr = [12, 23, 34, 45];
	const temPointer = Module.ccall('increment', 'number', ['array', 'number'], [arr, arr.length]);
	console.log(temPointer);

	let finalResult = [];
	for (let i = 0; i < arr.length; i++) {
		// 通过Module.getValue从共享线性内存中提取数据
		// 第一个参数是新数组中每个数据的起始内存地址 = 数组起始地址 + 偏移量
		// 第二个参数是数据内存模型，反映了数据宽度，'i8'对应1个字节
		// 因此这里的偏移量 = i * 1，若数据内存模型是'i64'对应8个字节，则偏移量 = i * 8
		finalResult.push(Module.getValue(temPointer + i, 'i8'));
	}
	console.log(finalResult);
});