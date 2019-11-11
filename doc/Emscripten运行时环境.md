## Emscripten运行时环境

**P341-P350**

> 如Module.ccall等由Emscripten运行时环境(Emscripten Runtime Environment,简称ERE)提供的封装好的内部方法，
> 实现了细节上屏蔽了JS与C/C++代码之间的运行时差异，使开发者专注于业务代码，不用过多考虑两个运行时之间的转换问题。    

### 输入/输出    

Emscripten工具链实现了一套与SDL(Simple DirectMedia Layer，简单直接媒体层)库完全对应的API接口，通过这些接口可以将原本基于SDL开发的应用移植到Web上。
SDL是一套跨平台的软件开发库，通过它我们可以直接访问计算机底层的音频，键盘，鼠标，游戏遥杆和图像硬件输入输出设备，进而它可以被用于开发高性能视频游戏，游戏开发引擎，以及各类多媒体应用程序。    

除了SDL,Emscripten在emsdk开发工具包中提供了一个html5.h头文件(emsdk\fastcomp\emscripten\system\include\emscripten\html5.h),该头文件定义了一系列可用于在C/C++中处理键盘事件，鼠标事件，设备方位，屏幕触摸和页面可见性等与底层I/O设备相关的交互逻辑接口。    

此外，Emscripten还对如下几种常见 底层图形设备处理库 提供了对等的web浏览器解决方案：    

- GLUT：(OpenGL Utility Toolkit)    

一个用于开发OpenGL应用程序的工具库，为OpenGL实现了一套简单的窗口化API。可在不了解窗口系统实现原理的情况下，简单编写出跨平台的3D应用程序。    

- GLFW：(Graphics Library Framework)    

一个专门用于编写OpenGL应用程序的轻量级C语言库，主要用于替代苦劳的GLUT工具库，它同样支持构建跨平台OpenGL应用开发。    

- GLEW：(OpenGL Extension Wrangler Library)    

一个跨平台且开源的C/C++扩展加载库。提供了高效的运行时机制。    

- XLib：(The X Library)    

一个基于C语言编写的是实现了 X Window 和 X Server 交互层协议的底层函数库。通过它我们可以在不知道相关协议细节的情况下编写桌面应用程序。    

### 文件系统    

传统的C/C++应用一般会使用libc和libxx标准库中提供的同步文件系统API来访问本地文件，
但由于浏览器的安全策略限制，我们无法直接在浏览器环境中访问本地主机系统中的文件。    

为此，Emscripten专门构建了一套针对libc和libxx库的浏览器实现，同时还构建了一个浏览器端的虚拟文件系统，
以便能正常编译并在web浏览器上运行使用了标准库 文件操作 相关API的C/C++程序。    

相比传统的本地文件系统，Emscripten所构建的虚拟文件系统则需要在应用运行前进行初始化：
将应用需要的本地文件系统中使用的所有文件，事先全部通过异步的JS API加载到浏览器的虚拟文件系统中。    

该虚拟文件系统具有多种文件系统类型可供选择：    

- MEMFS：默认，将文件存储于浏览器内存，页面重新加载会使文件内容丢失。

- IDBFS：允许将文件数据长时间保留在浏览器中以进行持久化处理。

- NODEFS：在Node.js环境中，该模式可直接访问真实的本地文件系统。

### 浏览器主循环    

Web内的事件模型使用了“协同多任务”处理机制，即每个事件每次只能在一个等长的时间片内运行，在该时间片结束后必须将控制权返回给浏览器，以便其他事件继续执行。通常导致html页面无响应的一个常见原因就是对应于当前事件的JS脚本没有及时退出并将控制权返回给浏览器，比如死循环或函数无限递归调用。    

而传统的C/C++图形应用通常会以无限循环的方式来执行一段代码(通常为渲染函数，比如GLUT中的glutMainLoop)，在这段代码中，应用程序分别负责处理事件，图形的计算和渲染，整个过程会通过添加延迟的方式来确保每一帧所花费的时间一致。但这种无限循环的代码执行方式无法直接用于浏览器环境，因为控制权无法在时间片内返回给浏览器，浏览器将通知用户页面无响应并停止提供服务。    

在浏览器环境中像WebGL这样的JS API 也只能在浏览器时间片结束时被执行，且在这些API内部会自动渲染和交换当前视图缓冲区的内容。这与基于OpenGL构建C/C++应用程序则正好相反，这里需要手动交换缓冲区的内容，以实现屏幕视图中显示内容的更新。Emscripten对这个问题的处理方案则是专门定义一个C/C++函数来代替图像处理代码中的无限循环过程：    

```
int main (int argc, char **argc) {
	...
	// 利用“__EMSCRIPTEN__”宏来区分编译环境
	#ifdef __EMSCRIPTEN__
	// void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
	// 在C/C++中模拟浏览器主循环，实际会编译成setTimeout + requestAnimationFrame实现
	
	// 以每秒60次饿频率调用one_iter_render(),两次执行之间执行其他浏览器事件代码
	emscripten_set_main_loop(one_iter_render, 60, 1);

	#else
	while (1) {
		one_iter_render();
		// 延迟绘制，使帧率稳定
		SDL_Delay(time_to_next_frame());
	}
	#endif
}

// 用于无限循环/主循环绘制函数
void one_iter_render () {
	//处理数据
	//绘制视图
}
```    

### 执行生命周期    

基于Emscripten工具链构建的Wasm应用其生命周期中各关键节点的基本执行顺序如图    

<img src='img/wasm-8.png'>    

左侧一列以“__”开头和结尾的标识符为Emscripten在JS运行时环境中提供的5种钩子队列数组，可在应用对应的JS代码中直接调用。    


- \_\_ATPRERUN\_\_ 应用开始运行前执行，这里一般进行虚拟文件系统初始化    
- \_\_ATINIT\_\_ Emscripten运行时环境开始初始化时    
- \_\_ATMAIN\_\_ C/C++源代码中的主函数被调用前    
- \_\_ATPOSTRUN\_\_ 当对应C/C++源代码中主函数的代码逻辑执行完毕后    
- \_\_ATEXIT\_\_ 整个应用/ERE退出时执行，这里可对之前分配的系统内存资源进行回收    


相应的，Emscripten也提供了一些可以应用在C/C++源代码中的生命周期函数，用于辅助模拟浏览器主循环流程(3个)，并对该流程进行控制(常用的4个)。    

- emscripten_set_main_loop()    

在C/C++源代码中模拟浏览器主循环的主要函数，实际Emscripten在编译时会直接转换为JS环境下对应的setTimeout和requestAnimationFrame    

- emscripten_push_main_loop_blocker()    

在emscripten_set_main_loop()运行前为其添加相应的预处理。比如进入游戏主流程前预先加载贴图，音视频等多媒体资源。该函数会阻塞主循环函数。    

- emscripten_async_call()    

用于在C/C++源代码中异步执行一段代码。不会被任何方法阻塞。可用它来执行任何需要在特定时间段后立即运行的任务。    

- emscripten_pause_main_loop()：暂停浏览器主循环    

- emscripten_resume_main_loop()：恢复浏览器主循环    

- emscripten_force_exit()：停止并强制退出当前wasm应用。函数调用后会直接触发当前JS运行时环境中的“__ATEXIT__”钩子队列。
若要在C/C++源代码中使用该函数，则需要在编译时为emcc指定参数“NO_EXIT_RUNTIME=0”，以允许Emscripten运行时环境退出。    

- emscripten_set_main_loop_expected_blockers()：用于向ERE报告预处理函数(emscripten_push_main_loop_blocker)的个数。
我们可以通过JS运行时环境提供的Module.setStatus回调函数，来实时检测位于执行队列中的预处理函数的总体完成进度，并同步的反馈给用户。    

更多与浏览器运行环境相关的函数，可查看源码：emsdk\fastcomp\emscripten\system\include\emscripten\emscripten.h，并在官网了解具体使用方法。    

### Emscripten内存表示    

Emscripten使用单一的“typed array(类型数组)”在JS环境与Wasm模块间传递数据。类型数组本身是基于ArrayBuffer构建的一段二进制缓存区。
与普通的JS数组不同的是，通过类型数组来存储数据可以以最小独立单元“比特”为单位(同C/C++)，这在某种程度上节省了内存。    

另外，基于类型数组，我们可以通过不同的类型视图来加载和读取内存中的数据。视图的类型决定了存储或读取数据时的数据类型。
比如HEAPU32表示以32位即4各字节为整体，从类型数组中读取或写入一个整数。    

