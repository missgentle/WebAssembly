__ATPRERUN__.push(() => {
	console.log("[__ATPRERUN__] prints from pre-loading stage ... ");
});

__ATINIT__.push(() => {
	console.log("[__ATINIT__] prints from init stage ... ");
});

__ATMAIN__.push(() => {
	console.log("[__ATMAIN__] prints from main stage ... ");
});

__ATPOSTRUN__.push(() => {
	console.log("[__ATPOSTRUN__] prints from post-loading stage ... ");
	// ����Module.setStatus�ص���������ʱ��ӡԤ��������ǰִ��״̬
	Module.setStatus = function (status) {
		console.log("[Module.setStatus]", status);
	}
});

__ATEXIT__.push(() => {
	console.log("[__ATEXIT__] prints from exit stage ... ");
});