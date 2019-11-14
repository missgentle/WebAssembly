__ATPOSTRUN__.push(() => {
	// 调用Module全局对象上的ccall方法
	const sqrtResult = Module.ccall('doubleSqrt', 'number', ['number'], [400]);
	console.log(sqrtResult);

	const capitalResult = Module.ccall('capitalize', 'string', ['string'], ["yhapy111"]);
	console.log(capitalResult);

	let arr = [12,23,34,45];
	const temPointer = Module.ccall('increment', 'number', ['array', 'number'], [arr, arr.length]);
	console.log(temPointer);

	let finalResult = [];
	for (let i = 0; i < arr.length; i++) {
		finalResult.push(Module.getValue(temPointer + i, 'i8'));
	}
	console.log(finalResult);
});
