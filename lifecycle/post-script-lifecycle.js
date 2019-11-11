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
	// 设置Module.setStatus回调函数，即时打印预处理函数当前执行状态
	Module.setStatus = function (status) {
		console.log("[Module.setStatus]", status);
	}
});

__ATEXIT__.push(() => {
	console.log("[__ATEXIT__] prints from exit stage ... ");
});
