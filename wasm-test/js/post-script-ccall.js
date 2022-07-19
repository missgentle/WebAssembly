__ATPOSTRUN__.push(() => {
	// ����Moduleȫ�ֶ����ϵ�ccall����
	const sqrtResult = Module.ccall('doubleSqrt', 'number', ['number'], [400]);
	console.log(sqrtResult);

	const capitalResult = Module.ccall('capitalize', 'string', ['string'], ["yhapy111"]);
	console.log(capitalResult);

	// ����ccall����֧��array����ֵ���ͣ�������һ��������number���͵��������׵�ַ
	let arr = [12, 23, 34, 45];
	const temPointer = Module.ccall('increment', 'number', ['array', 'number'], [arr, arr.length]);
	console.log(temPointer);

	let finalResult = [];
	for (let i = 0; i < arr.length; i++) {
		// ͨ��Module.getValue�ӹ��������ڴ�����ȡ����
		// ��һ����������������ÿ�����ݵ���ʼ�ڴ��ַ = ������ʼ��ַ + ƫ����
		// �ڶ��������������ڴ�ģ�ͣ���ӳ�����ݿ�ȣ�'i8'��Ӧ1���ֽ�
		// ��������ƫ���� = i * 1���������ڴ�ģ����'i64'��Ӧ8���ֽڣ���ƫ���� = i * 8
		finalResult.push(Module.getValue(temPointer + i, 'i8'));
	}
	console.log(finalResult);
});