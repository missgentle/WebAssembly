// "胶水工具" 解决了大多数原生到Web的跨平台问题
#include <emscripten.h>

// 条件编译 在C++编译器中以C语言的规则来处理代码，防止Name Mangling处理
#ifdef __cplusplus
extern "C"{
#endif

// 利用宏防止函数被DCE
EMSCRIPTEN_KEEPALIVE int add(int x, int y){
	return x + y;
}

#ifdef __cplusplus
}
#endif