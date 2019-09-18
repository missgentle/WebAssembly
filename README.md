# WebAssembly
let C/C++ to run in the browser    
简书优质文章 https://www.jianshu.com/p/bff8aa23fe4d    

## 深入浅出 WebAssembly 观书有感 & 学习笔记

Github链接：https://github.com/Becavalier/Book-DISO-WebAssembly

### 序言 & 第一章 漫谈WebAssembly发展史

#### 2019.09.17

> 首先，吐槽一下，第一章漫谈发展史，一谈就是90页，这也太漫了吧，截至今天才看到 17页 －_－b    
> 虽然刚看到17页，出身计算机专业的我感觉内容已经硬核到快啃不动了，好家伙编译原理没学好的连发展史都无法了解吗？    

以下进入正题，整理今日份学习笔记：

**序言**
- WebAssembly是一种新型的二进制格式，文件体积更小，启动速度&运行速度更快；
WebAssembly是多种编程语言的编译目标，包括C和C++；
WebAssembly开始被应用于Web浏览器之外的领域，如区块链和内容分发网络(CDN);
最初出现在Firefox中的ASM.js让业界开始关注于解决跨浏览器协作，以便让原生代码运行在浏览器上；
WebAssembly会在将来添加多线程，SIMD，GC等功能，这些新特性将带来更多的可能性；
WebAssembly的出现让我们能够以极小的成本来复用其他领域已存在的成果，以此弥补JS性能与功能上的不足。

**前言**
- JS本身作为一种弱类型语言，相比于C/C++等强类型语言，尽管Chrome V8，SpiderMonkey等JS引擎已经通过诸如JIT等技术手段来优化JS脚本代码的整体执行效率，
但引擎每一次每一次版本优化的迭代速度却远跟不上当今各类Web应用的复杂度变化。因此，发明一种能够根本上解决该问题的技术迫在眉睫。

- 昙花一现的ASM.js，NaCl，PNaCl等技术都尝试以各自的方式来优化Web应用的执行效率，但由于诸如“浏览器兼容性不佳”，“性能优化不彻底”等问题，导致最终没有被广泛推广。而在2015年出现的WebAssembly(简称Wasm)，便是在吸取了前者的经验教训的基础上被设计和发明出来的。现在，W3C成立了专门的WWG工作组负责WebAssembly技术的标准迭代与实现，四大主流浏览器(Chrome,Firefox,Edge,Safair)已经全部实现WebAssembly技术在其MVP标准中的制定的所有特性，C/C++,Go和Rust等高级语言已经逐渐开始支持编译到Wasm格式。

**第一章正文**

- 基准测试 **P8**
  - 测试代码：浮点数累加一亿次，并循环执行10次
  - 参与测试的语言：C++(包括经过编译器优化和浮点数操作优化和未经过任何优化的)，Java，JS，Python
  - 平均耗时结果：优化后的C++ 3ms，Java 103ms，JS 105ms，未经优化的C++ 306ms，Python  6022ms    

- Web新时代与挑战 **P11**    

框架在一些必要的业务流程上已经做了足够多的封装和优化，是我们能更多的关注业务逻辑的实现，而不是一些底层的架构细节。但事情并没有那么完美，以Node.js为例，由于其本身基于V8实现，而V8最重要的功能就是对JS代码进行解析和优化，然后将优化好的中间代码编译成机器码或其他格式后在进行处理。因此，无论Node.js对V8上层的JS代码进行了何种底层系统调用流程上的优化，如果最后V8在解析和优化JS代码的过程中消耗了大量时间，那么整个应用的运行效率必然会大打折扣。总的来说，Chrome V8，JavaScriptCore和SpiderMonkey等JS引擎对JS代码的解析和优化效率，直接决定了基于JS开发的前端和服务器端应用的运行效率和用户体验。此外，日益庞大的Web前端应用给JS语言性能上带来的挑战，日益复杂的页面交互带来巨大的DOM节点修改成本也是未来我们要面对的问题。

- 非终结符、终结符与产生式 **P16**

终结符：词法分析中产生的最小的且具有明确语义的有效关键字(Token)。    

用S表示表达式，v表示变量，e表示=，d表示整数，p表示+，E表示非终结符，则加法运算结果赋值给一个变量的产生式如下：    

E -> d|Epd  (非终结符展开)    
S -> ve(d|Epd)    

表达式S：aVariable = 1+2+3; 

#展开过程 ( **勘误** )    

1. S -> veE (E -> Epd)    
2. S -> veEpd (E -> Epd)    
3. S -> veEpdpd (E -> d)    
4. S -> vedpdpd

----------------------------------------------------------华丽丽的分界线-------------------------------------------------------

#### 2019.09.17

- 编译器链路 **P16+P22**

通常，在编程语言所对应的整个编译器链路中，词法分析器(Lexer)负责将源码中各类短语进行过滤并解析成具有特定语义的Token字符串，接下来，在语法分析阶段，这些字符串会被语法分析器(Parser)通过相应算法进行“表达式非终结符展开”的处理。如果语法分析器无法将一段代码内的某个表达式展开成标准中提到的任意一种终结符展开式形式，那么该表达式中一定存在语法错误。语法分析器在处理完代码后会向编译器链路的下一个阶段输出一种名为“抽象语法树(AST)”的数据结构，它以结构化的表示形式表达了整段代码的语法结构。至此也表明了语法分析器真正“理解”了源码中各代码段的具体语义。在随后的语义分析阶段，编译器会进一步分析AST，进而判断代码是否存在运行时错误，并做一些初步优化生成中间代码。最后编译器会将得到的中间代码直接编译成目标平台的机器码。

- 弱类型与强类型 **P16**

JS本身是一种弱类型(Weak Typed)的编程语言。所谓弱类型，在语法形式上的直观体现就是初始化变量时，无需显式指定变量类型，其类型完全由代码解释器在代码运行过程中进行推断。相对的，强类型(Strongly Typed)编程语言，最直观的体现是声明变量时，必须显式指定变量需要存储的数据类型。这样做的好处是，无须再花费额外的时间在代码运行时去推断变量的数据类型，这从某种程度上可以大大提高代码的运行效率。由于代码中的所有变量类型都不需要通过运行时环境推断，因此便可以提前将程序源码进行静态编译(AOT)和优化，最后直接生成相应的经过优化的二进制机器码供CPU执行。

- Chrome V8 引擎链路 **P17+P22**

<img src='img/wasm-1.png'>    

老版本的Chrome V8(Chrome 58以下)，整个代码的解析，编译和执行过程流程，可以分为两个阶段：Baseline编译阶段和Optimized编译阶段。Baseline编译阶段由“Full-codegen”基线JIT编译器处理，Optimized编译阶段由“Crankshaft”和“TurboFan”两个优化JIT编译器处理。每一组编译器都有一个前置的语法分析器，对JS源码进行词法和语法分析，同时生成对应的AST数据结构。    










