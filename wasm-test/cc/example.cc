int main (int argc, char **argc) {
	...
	// 利用“__EMSCRIPTEN__”宏来区分编译环境
	#ifdef __EMSCRIPTEN__
	// void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
	// 在C/C++中模拟浏览器主循环，实际会编译成setTimeout + requestAnimationFrame实现
	
	// 以每秒60次饿频率调用one_iter_render(),两次执行之间执行其他浏览器事件代码
	emscripten_set_main_loop(one_iter_render, 60, 1);

	#else
	while (1) {
		one_iter_render();
		// 延迟绘制，使帧率稳定
		SDL_Delay(time_to_next_frame());
	}
	#endif
}

// 用于无限循环/主循环绘制函数
void one_iter_render () {
	//处理数据
	//绘制视图
}