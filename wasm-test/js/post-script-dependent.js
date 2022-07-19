//向Module初始化完毕的钩子队列中加入待执行的内容
__ATPOSTRUN__.push(() => {
	//调用模块中暴露出的echo方法
	Module.ccall('echo', null, ['number'], [10]);
	//也可以这样调用
	Module['asm']['echo'](10);
})