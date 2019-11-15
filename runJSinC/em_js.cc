#include <emscripten.h>
#include <iostream>

using namespace std;

// 定义一个add函数，函数体由JS实现，声明由C实现
EM_JS(int, add, (int x, int y), {
	console.log(x, y);
	return x + y;
});

int main(int argc, char **argv) {
	// 直接调用add函数
	cout << add(1, 2) << endl;
	return 0;
}
