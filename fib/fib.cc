#include <emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

	int EMSCRIPTEN_KEEPALIVE fib(int x) {
		if(x < 2) {
			return 1;
		} else {
			return fib(x - 1) + fib(x - 2);
		}
	}

#ifdef __cplusplus
}
#endif
