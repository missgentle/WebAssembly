#include <emscripten.h>
#include <iostream>
#include <string>

using namespace std;

int counter = 0;
int blockerNumbers = 5;
int *p = &counter;

// 主循环
void one_iter_render (void) {
	cout << "[emscripten_set_main_loop] prints from main loop ... "
	 << counter++ << endl;
	if(counter == 5){
		emscripten_pause_main_loop();
		emscripten_force_exit(1);
	}
}

// 预处理
void one_iter_block (void* args){
	cout << "[emscrpten_push_main_loop_blocker] prints from main loop blocker ... "
	 << *static_cast<int*>(args) << endl;
}

// 需要异步执行的代码逻辑
void one_iter_async (void* args){
	cout << "[emscripten_async_call] prints from JS conext async ... " << endl;
}

// C/C++主程序
int main (int argc, char **argv){

	// 设置5个预处理，这将阻塞主循环函数
	emscripten_push_main_loop_blocker(one_iter_block, p);
	emscripten_push_main_loop_blocker(one_iter_block, p);
	emscripten_push_main_loop_blocker(one_iter_block, p);
	emscripten_push_main_loop_blocker(one_iter_block, p);
	emscripten_push_main_loop_blocker(one_iter_block, p);

	// 报告预处理个数
	emscripten_set_main_loop_expected_blockers(blockerNumbers);
	// 设置异步代码的执行条件
	emscripten_async_call(one_iter_async, nullptr, 2000);
	// 设置主循环函数
	emscripten_set_main_loop(one_iter_render, 1, 1);

	return 0;
}
