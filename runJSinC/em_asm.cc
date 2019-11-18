#include <emscripten.h>

int main(int argc, char **argv) {

	// EM_ASM
	EM_ASM(console.log("Hello,WebAssembly! #1"));

	// EM_ASM_
	int x = 100;
	int y = 200;
	EM_ASM_({
		console.log("This is value from C: ", $0, $1);
	}, x, y);

	// EM_ASM_INT
	int z = EM_ASM_INT({
		console.log("This is value from C: ", $0);
		return $0 + 1;
	}, y);

	// EM_ASM_DOUBLE
	double result = EM_ASM_DOUBLE({
		console.log("This is value from C: ", $0);
		return $0 + 0.1;
	}, z);

	EM_ASM_({console.log("Result :", $0)}, result);

	return 0;
}
