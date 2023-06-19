​	[012] [ARM-Cortex-M3/4] 异常与中断处理流程

![img](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/original.png)

[柯西的彷徨](https://blog.csdn.net/kouxi1)![img](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/newUpTime2.png)已于 2022-03-22 01:44:37 修改![img](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/articleReadEyes2.png)2618![img](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/tobarCollect2.png) 收藏 22

分类专栏： [ARM](https://blog.csdn.net/kouxi1/category_11633790.html) 文章标签： [stm32](https://so.csdn.net/so/search/s.do?q=stm32&t=all&o=vip&s=&l=&f=&viparticle=) [arm](https://so.csdn.net/so/search/s.do?q=arm&t=all&o=vip&s=&l=&f=&viparticle=)

版权

[![img](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/resize,m_fixed,h_224,w_224.jpeg)ARM专栏收录该内容](https://blog.csdn.net/kouxi1/category_11633790.html)

19 篇文章16 订阅

订阅专栏

ARM
Contents异常与中断处理流程程序执行方式处理流程保存与恢复现场为什么要保存现场需要保存的现
场（寄存器）M3/4硬件保存与
恢复现场流程

# 1 异常与中断处理流程

## 1.1 程序执行方式

[ARM](https://so.csdn.net/so/search?q=ARM&spm=1001.2101.3001.7020)中控制程序执行的三种方式：

1. 正常程序是顺序执行的，在CM3中每执行一条指令，PC += 4；
2. 通过跳转指令，程序可以跳转到特定的地址标号/特定的子程序处执行；
3. 当异常/中断发生时，系统**执行完当前指令后**，将跳转到相应的ESR/ISR处执行。当执行完后程序**返回发生中断的指令的下一条指令**处执行。（进入ESR/ISR前先保护被中断程序的执行现场，从异常程序退出时，要恢复现场）

## 1.2 处理流程

- 初始化
  - 设置中断源
  - 设置中断控制器（中断屏蔽寄存器组、优先级）
  - 设置CPU总开关，使能中断
- 执行正常程序
- 产生中断->中断信号发给中断控制器->CPU
- CPU每执行完一条指令，都会检查有无中断/异常产生（硬件）
- 发现有异常/中断产生->开始处理：
  - 保护现场
  - 分辨异常/中断，调用对于异常/中断的处理函数
  - 恢复现场

### 1.2.1 Cortex-M3/4处理流程

参考资料：`DDI0403E_B_armv7m_arm.pdf`、`ARM Cortex-M3与Cortex-M4权威指南.pdf`、`PM0056.pdf`

![image-20220316203733443](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/b9b2f2bce46a777fe5bf566b19645cba.png)

- 保存现场（硬件）：把被中断瞬间的寄存器的值保存进栈里
- 分辨异常/中断（硬件）
- 根据异常/中断号，从向量表中得到**函数地址**，跳转过去执行
- 函数执行完后，从栈中恢复现场（软件触发，硬件恢复）

### 1.2.2 Cortex-A7处理流程

参考资料：`ARM ArchitectureReference Manual ARMv7-A and ARMv7-R edition.pdf`

![image-20220316204101536](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/3aca4961d878be1c337125b08180f232.png)

- CPU切换到对应的异常模式

  - 用户模式（usr）
  - 快速中断模式（fiq）
  - 外部中断模式（irq）
  - 特权模式（sve）
  - 中止模式（abort）
  - 未定义指令模式（undefined）
  - 系统模式（sys）

- 保存被中断时的CPSR到SPSR

  - CPSR：current program status register，当前程序状态寄存器
  - SRSR：saved program status register，保存的程序状态寄存器

- 向量表上放置的是

  跳转指令

  （如发生任何中断时，CPU会从向量表里找到下面第6项（0~7），得到

  ```
  ldr pc, _irq
  ```

  指令，执行后就跳转到_irq函数），在跳转到的函数中：

  - 保存现场
  - 分辨异常/中断
  - 调用对应的处理函数
  - 恢复现场

```assembly
_start: 
    b	reset
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq
123456789
```

上面启动代码来自：[u-boot-arch-arm-lib-vectors.s](https://source.denx.de/u-boot/u-boot/-/blob/master/arch/arm/lib/vectors.S)

综上，**两者区别**：

- 保存现场：cortex M3/M4里是硬件完成，cortex A7等是软件实现
- 分辨异常/中断：cortex M3/M4里是硬件完成，cortex A7等是软件实现
- 调用处理函数：cortex M3/M4里是硬件来调用，cortex A7等是软件自己去调用
- 恢复现场：cortex M3/M4里是软件触发、硬件实现，cortex A7等是软件实现

# 2 保存与恢复现场

## 2.1 为什么要保存现场

举例分析：

![image-20220322012630727](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/19fa47b1502c6c9c5df863eb879e7a75.png)

上述4条汇编指令，它们被异常打断时，需要保证在异常处理完后，被打断的程序还能正确运行，需要保存的数据：

- 执行**完**第1条指令时程序被打断，恢复运行时，R0要保持不变
- 执行**完**第2条指令时程序被打断，恢复运行时，R0、R1要保持不变
- 执行**完**第3条指令时程序被打断，比较结果保存在**程序状态寄存器**里，恢复运行时，程序状态寄存器保持不变

上述指令要读取a、b内存，当被打断时无需保存，因为**只要程序不越界，内存就保持不变**。因此关键在于**R0、R1、程序状态寄存器**的保存：

- 在处理异常前，把这些寄存器保存在**栈**中，即为**保存现场**
- 在处理完异常后，从**栈**中恢复这些寄存器，即为**恢复现场**

## 2.2 需要保存的现场（寄存器）

![image-20220316235000381](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/4abbe7bc2a1ea85b87b55daaa9024bd7.png)

根据[ATPCS](https://blog.csdn.net/kouxi1/article/details/123039106)：C函数可以修改R0~R3、R12、R14（LR）及PSR寄存器（M3/M4中称为`XPSR`，A7中称为`CPSR`）。若C函数需要使用R4~R11，就应该把它们保存到栈里，在函数结束前在从栈中恢复它们。

因此，寄存器被拆分成2部分：

- **调用者**保存的寄存器(R0-R3,R12,LR,PSR)：函数调用子程序后，若还需使用其中某些寄存器，则在调用前需保存到栈中，调用结束后再从栈中恢复。
- **被调用者**保存的寄存器(R4-R11)：被调用者需要使用其中某些寄存器时，则需将它们保存到栈中，函数退出前恢复它们的原始值，因此其他程序可能在使用这些寄存器。

例如，函数A（调用者）调用函数B（被调用者）时：

对于函数A：

- R0-R3用来传参数给函数B，函数B可能会修改这些寄存器，函数A若还需使用，则必须保存它们；
- R12，LR，PSR若还需使用，也要保存

对于函数B：

- 用到R4-R11中的某些寄存器，都要在函数入口保存、在函数返回前恢复
- 保证在B函数调用前后，函数A看到的R4-R11保持不变

函数B就可以视为异常/中断处理函数，在函数A被打断，执行异常/中断处理前，需要保存：

- 保存调用者使用到的寄存器(R0-R3,R12,LR,PSR)
- PC

## 2.3 M3/4硬件保存与恢复现场流程

### 2.3.1 异常堆栈帧（exception stack frame）

在异常入口处被压入栈空间的数据块为**栈帧**。对于[Cortex-M3](https://so.csdn.net/so/search?q=Cortex-M3&spm=1001.2101.3001.7020)或不具有浮点单元的Cortex-M4处理器，栈帧都是`8`个字（32字节）大小的，对于具有浮点单元的Cortex-M4则可能是8或26个字。

ATPCS要求栈指针的数值在函数入口和出口处是双字对齐的，即SP的值**必须能被8整除**，若在中断产生时栈帧未对齐到双字上，M3/4会自动插入一个字（栈本身即是字<4字节>对齐的），双字对齐特性可通过`SCB->CCR`的STKALIGN位设置，若异常不符合ATPCS，则可将该特性关闭。（**F1默认不开启，但启动文件使用`PRESERVE8`做了8字节对齐**）也可以通过伪指令`REQUIRE8`和`PRESERVE8`配置堆栈8字节对齐。

进入异常前，依次把xPSR, PC, LR, R12以及R3-R0由**硬件自动**压入适当的堆栈中（响应异常时，若当前代码正在使用PSP，则压入PSP，否则就压入MSP），其中，**PC（`SP-0x24`处）即为图中返回地址**：

![image-20220319163920075](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/9cbff2f1de1a3399b30f36343ed64f35.png)

▲ 双字栈对齐时，Cortex-M3或Cortex-M4(无浮点单元)处理器的异常栈帧

压栈时xPSR的bit9表示栈指针SP数值是否被调整过，上图为双字对齐，因此不会额外插入一个字，且`xpsr bit9 = 0`。若使能了双字对齐特性，且SP数值未对齐到双字边界上，栈中会被插入一段空间，SP被强制对齐到双字地址，且`xpsr bit9 = 1`，表明插入了一段区域：

![image-20220319172123214](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/b55be99395e61fe0f5c2dcf6e6682a38.png)

▲ 非双字栈对齐时，Cortex-M3或Cortex-M4(无浮点单元)处理器的异常栈帧

在**自动入栈**的过程中，把寄存器写入堆栈内存的**时间顺序**，并不是与写入的**空间顺序**相对应的。但是机器会保证：正确的寄存器将被保存到正确的位置：

![image-20220319171342774](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/e08ce565ea24c93a6b2967ea2f802065.png)

▲ 内部入栈序列

- 先保存PC与xPSR：可以更早地启动服务例程指令的预取——因为这需要修改PC；同时，也做到了在早期就可以更新xPSR中`IPSR位段`的值。
- 后压入R3-R0,R12：为了更容易地使用SP基址来索引寻址（这也方便了LDM等多重加载指令。因为LDM必须加载地址连续的一串数据，而现在R0-R3, R12的存储地址连续了），这种顺序也舒展了参数的传递过程，即可方便地通过读取入栈的R0-R3取出参数

**入栈**操作由**数据（系统）总线**完成，而**指令总线**同时会从向量表中找出正确的**异常向量**，然后在服务程序的入口处预取指，即**入栈和取指同时进行**。

### 2.3.2 更新寄存器

在入栈和取向量操作完成之后，执行服务例程之前，还要更新一系列的寄存器：

- SP：在入栈后会把堆栈指针（PSP或MSP）更新到新的位置。在执行服务例程时，将由MSP负责对堆栈的访问。
- PSR：更新IPSR位段的值为新响应的异常编号。
- PC：在取向量完成后，PC将指向服务例程的入口地址
- LR：LR = `EXC_RETURN`

此外，NVIC中也会更新若干个相关有寄存器。

### 2.3.3 异常返回EXC_RETURN

M3/M4在调用异常处理函数前，把LR设置为一个特殊的值——`EXC_RETURN`，当异常处理结束后，**硬件**将`PC=EXC_RETURN`，触发**异常返回机制**：

- 恢复先前压入栈中的寄存器，堆栈指针的值也改回先前的值。
- 更新NVIC寄存器：活动位被硬件清除，对于外部中断，倘若中断输入再次被置为有效，悬起位也将再次置位。

`EXC_RETURN`合法值如下：

![image-20220317013032668](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/8e04adb0358fbad48bbb42ff11a3b918.png)

▲ EXC_RETURN的位域

![image-20220317013205472](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/ba2357d360c566e2ffbe722a6c074250.png)

▲ EXC_RETURN的合法值

如果主程序在**线程模式**下运行，并且在使用MSP时被中断，则在服务例程中LR=0xFFFF_FFF9；若使用PSP时被中断，则在服务例程中LR=0xFFFF_FFFD（主程序被打断前的LR已被自动保存至异常栈帧）：

![image-20220320222716951](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/c44403673e1bc88b3a4af2ad44f6979d.png)

如果主程序在**Handler模式**（**MSP**）下运行，则在服务例程中LR=0xFFFF_FFF1，在**嵌套**时，更深层ISR所看到的LR总是0xFFFF_FFF1：

![image-20220320222909813](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/b54c187ac6703b7628f7461f33258c2a.png)

**执行异常返回**：

- 可通过`EXC_RETURN bit2`判断异常返回的栈帧使用的是MSP还是PSP
- 在每次出栈操作结束时，处理器还会检查出栈xPSR数值的第9位，并且若压栈时插入了额外的空间则会将其去除。

![image-20220320222512480](%5BARM-Cortex-M34%5D%20%E5%BC%82%E5%B8%B8%E4%B8%8E%E4%B8%AD%E6%96%AD%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.assets/535e97f6ee63b844d4a184dd85d91f6b.png)

*END*





## 以上

意思是发生中断，pc指针强制条跳转到初始向量表表头,这里是0x800 0000地址，然后由偏移量和中断号计算得到相应中断服务函数在向量表中的位置，再跳转过去。

