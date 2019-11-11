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



### 执行生命周期    



### Emscripten内存表示    



