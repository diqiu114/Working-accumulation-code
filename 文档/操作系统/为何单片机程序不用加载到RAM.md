# [为何单片机程序不用加载到RAM](https://www.cnblogs.com/linux-37ge/p/10531437.html)

# 一. STM32程序构成

## 　　1.1. STM32的存储空间

　　　　1.1.1. RAM

　　　　　　1.1.1.1 单片机的RAM是SRAM.

　　　　　　1.1.1.2. SRAM特点

　　　　　　　　a.优点，速度快，不必配合内存刷新电路，可提高整体的工作效率，软件上不需要初始化SRAM。
         　　　b. 缺点，集成度低，功耗较大，相同的容量体积较大，而且价格较高，少量用于关键性系统以提高效率。
　　　　　　　　c. SRAM使用的系统：
　　　　　　　　　　（1）CPU与主存之间的高速缓存。
　　　　　　　　　　（2）CPU内部的L1/L2或外部的L2高速缓存。
　　　　　　　　　　（3）CPU外部扩充用的COAST高速缓存。

　　　　　　　　　　（4）单片机内存单元

　　　　1.1.2. FLASH

　　　　　　1.1.2.1. 单片机的flash是NorFlash

　　　　　　1.1.2.1. NorFlash 特点

　　　　　　　　a. NOR可以直接使用，并可在上面直接运行代码。不需要初始化

　　　　　　　　b. NOR flash带有SRAM接口，有足够的地址引脚来寻址，可以很容易地存取其内部的每一个字节

　　　　1.1.3. NOR FLASH 和 NAND FLASH对比

　　　　　　![img](%E4%B8%BA%E4%BD%95%E5%8D%95%E7%89%87%E6%9C%BA%E7%A8%8B%E5%BA%8F%E4%B8%8D%E7%94%A8%E5%8A%A0%E8%BD%BD%E5%88%B0RAM.assets/1565092-20190314160821299-231439338.png)

　　　　　　a.NOR与NAND特性的差别，主要是由于其内部“地址/数据线”是否分开导致的。由于 NOR的地址线和数据线分开，它可以按“字节”读写数据，符合 CPU 的指令译码执行要求，所以假如 NOR上存储了代码指令， CPU 给 NOR一个地址， NOR 就能向CPU 返回一个数据让 CPU 执行，中间不需要额外的处理操作。

　　　　　　b.由于 NAND 的数据和地址线共用，只能按“块”来读写数据，假如 NAND 上存储了代码指令， CPU 给 NAND 地址后，它无法直接返回该地址的数据，所以不符合指令译码要求。 即不支持立即执行的特性(eXecute In Place)，若代码存储在NAND上，可以先把它加载到RAM存储器上，再由CPU执行。　　

## 　　1.2. 空间排布

![img](%E4%B8%BA%E4%BD%95%E5%8D%95%E7%89%87%E6%9C%BA%E7%A8%8B%E5%BA%8F%E4%B8%8D%E7%94%A8%E5%8A%A0%E8%BD%BD%E5%88%B0RAM.assets/1565092-20190314161518743-45929925.png)

　　　　1.2.1. keil编译信息分析

　　　　　　1.2.1.1. code: 表示程序代码部分

　　　　　　1.2.1.2. RO-data: 表示程序中定义的常量（如：const ,字符串）

　　　　　　1.2.1.3. RW-data: 表示已初始化的全局变量 

　　　　　　1.2.1.4. ZI-data: 表示未初始化或初始化为0的全局变量

　　　　　　1.2.1.5. 大小计算

　　　　　　　　a. RO Size = Code + RO Data   (程序占用FLASH空间）

　　　　　　　　b. RW Size = RW Data + ZI Data (运行时程序占用RAM空间）

　　　　　　　　c. ROM Size = Code + RO Data + RW Data (烧录时程序占用FLASH 空间的大小，bin文件）

　　　　　　　　　　**PS: 为什么bin文件不包含ZI Data**

　　　　　　　　　　　　**答：因为ZI 数据都是0，只要程序运行前将ZI数据所在的区域（RAM区域）一律清零即可，如此节省了flash储存空间**

# 二. 程序是否需要加载到RAM中？

## 　　2.1. 单片机是否需要？

　　　　2.1.1. 把程序从flash加载到RAM需要bootloader，（其实程序也可以直接下载到RAM中运行，只不过重启程序就没有了。在flash刷新次数受限（一般flash可以刷新1000次左右）直接烧录程序到RAM调试程序。

　　　　2.1.2. 单片机RAM较小程序太多无法加载全部程序

　　　　2.1.3. 单片机执行分三个步骤：取指令，分析指令，执行指令。取指令任务是根据PC值从地址总线上读出指令。虽然从RAM取指令速度远大于ROM,但单片机自身运行速度不高，并不影响速度

 　　　 2.1.4. 总结：虽然单片机可以把程序加载到RAM, 但真的真的没必要这么干。

## 　　2.2. 运行Linux系统为什么需要？

　　　　2.2.1. linux程序比较大，很少用norflash储存程序，而是用nandFlash或sd储存，故这类储存 不符合CPU 的指令译码执行要求。

　　　　2.2.2. 运行linux系统的cpu。其运行频率非常高，远大于ROM读写速度，从rom取指会严重影响速度。故系统会把程序拷贝到RAM执行。

　　　　2.2.3. **总结：运行Linux系统时程序必须加载到RAM，单片机由于nor flash原因，可以不载入到ram运行程序，电脑用的是另一种**