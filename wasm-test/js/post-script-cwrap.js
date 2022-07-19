__ATPOSTRUN__.push(() => {
	// ����Moduleȫ�ֶ����ϵ�cwrap�������ذ�װ����
	const sqrtFunc = Module.cwrap('doubleSqrt', 'number', ['number']);
	console.log(sqrtFunc);
	console.log(sqrtFunc(400));

	const capitalFunc = Module.cwrap('capitalize', 'string', ['string']);
	console.log(capitalFunc);
	console.log(capitalFunc('nice666'));

	let arr = [12, 23, 34, 45];
	const temFunc = Module.cwrap('increment', 'number', ['array', 'number']);
	console.log(temFunc);
	console.log(temFunc(arr, arr.length));

	let finalResult = [];
	for (let i = 0; i < arr.length; i++) {
		finalResult.push(Module.getValue(temFunc(arr, arr.length) + i, 'i8'));
	}
	console.log(finalResult);
});