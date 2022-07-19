#include <iostream>
#include <emscripten.h>

using namespace std;

// 函数将接收一个从JS环境传递过来的指针
extern "C" void EMSCRIPTEN_KEEPALIVE wrapper(int fp){
	// 定义目标函数类型
	using fpt = void (*) (int);
	cout<< "The function pointer is : " << fp << endl;
	// 对传递过来的int类型的指针进行类型转换
	fpt f = reinterpret_cast<fpt>(fp);
	// 通过指针调用对应的JS函数
	f(7);
	// 清理函数索引表
	EM_ASM({
		Module.removeFunction($0);
	}, f);
}
