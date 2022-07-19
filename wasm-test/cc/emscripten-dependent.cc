#include <emscripten.h>
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

EMSCRIPTEN_KEEPALIVE void echo(int x){
	cout << "The number you input is: " << x << endl;
}

#ifdef __cplusplus
}
#endif