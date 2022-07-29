#include <emscripten.h>
#include <iostream>
#include <string>

using namespace std;

int counter = 0;
int blockerNumbers = 5;
int *p = &counter;

// 主循环
void one_iter_render(void)
{
	cout << "[emscripten_set_main_loop] 主循环 ... "
			 << counter++ << endl;
	if (counter == 3)
	{
		emscripten_pause_main_loop(); // 暂停浏览器主循环
		emscripten_resume_main_loop(); // 恢复浏览器主循环
	}
	if (counter == 8)
	{
		emscripten_force_exit(1); // 停止并强制退出当前wasm应用
	}
}

// 预处理 会阻塞主循环
void one_iter_block(void *args)
{
	cout << "[emscrpten_push_main_loop_blocker] 预处理 ... "
			 << *static_cast<int *>(args) << endl;
}

// 需要异步执行的代码逻辑 不会被任何方法阻塞
void one_iter_async(void *args)
{
	cout << "[emscripten_async_call] 异步操作 ... " << endl;
}

// C/C++主程序
int main(int argc, char **argv)
{

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