#include <iostream>

using namespace std;

int add(int x, int y){
return x + y;
}

int main(int argc, char **argv){
cout << "Hello,Emscripten!\n" << "Result:" << add(10, 20) << endl;
return 0;
}
