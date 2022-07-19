#include <iostream>
#include <math.h>

using namespace std;

extern "C" {
	// 声明在外部模块中定义的custom_add函数
	extern int custom_add (int x, int y);
}

int main() {
	int x = 10, y = 100;
	// 调用custom_add
	cout << custom_add(x, y) << endl;
	return 0; 
}