#include <cmath>
#include <emscripten.h>

extern "C" {
	double EMSCRIPTEN_KEEPALIVE doubleSqrt(double x){
		return sqrt(x);
	}

	// 参数为C-style字符串
	unsigned char* EMSCRIPTEN_KEEPALIVE capitalize (unsigned char *string) {
		int i = 0;
		while (1){

			// 获取每个字符的ASCII码
			char _current_pos = *(string + i);
			// 转换为大写形式
			if (_current_pos >= 0x61 && _current_pos <= 0x7a){
				*(string + i) = _current_pos -32;
			}

			// 若处理到字符串结尾则退出循环
			if (_current_pos == '\0') {
				break;
			}

			i++;
		}
		return string;
	}

	// 将数组内所有元素的值加1
	char* EMSCRIPTEN_KEEPALIVE increment (char array[], int length) {
		for (int i = 0; i < length; i++) {
			array[i] += 1;
		}
		return array;
	}
}