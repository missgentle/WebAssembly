// 定义待排序数组的大小
#define N 10
// 定义将从JS环境导入的函数
extern void print(int* offset, int length);
// 声明用于排序的全局数组，在模块初始化时便已在内存中生成
int array[N];

// 用于在JS环境中获取待排序数组首地址的方法
int* getArrayOffset(){
	return array;
}

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

// 核心的快速排序方法
void quicksort_core(int array[], int maxlen, int begin, int end){
	int i, j;
	if(begin < end){
		i = begin + 1;
		j = end;
		while(i < j){
			if(array[i] > array[begin]){
				swap(&array[i], &array[j]);
				j--;
			} else {
				i++;
			}
		}
		if(array[i] >= array[begin]){
			i--;
		}
		swap(&array[begin], &array[i]);
		quicksort_core(array, maxlen, begin, i);
		quicksort_core(array, maxlen, j, end);
	}
}

// 用于在JS环境中调用的主排序的方法
void sort(){
	quicksort_core(array, N, 0, N - 1);
	// 调用从JS环境导入的“打印”方法并将数组作为参数传入
	print(array, N);
}