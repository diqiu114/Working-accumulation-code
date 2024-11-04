# uboot数组越界导致启动失败问题

 Posted on 2024-10-28 In [debug](http://coffepattern.top/categories/debug/) Views: 15

uboot数组越界导致启动失败问题

# 问题背景

这几天我们有一款芯片的evb板要换支持1.8v的板子，硬件部门将板子rework好后，这个活交由我们团队另一名同事去测试，结果这位同事反映，在dts中通过pinctrl的of机制配置gmac引脚电压后，电压可以成功配置成功，但是在启动时会报错：

```
"Synchronous Abort" handler, esr 0x02000000                                     
elr: ffffffff812da000 lr : 000000000103fe74 (reloc)                             
elr: 0000000000200000 lr : 000000007ff65e74                                     
x0 : 000000007df1f5e0 x1 : 0000000000200000                                     
x2 : 000000000000000a x3 : 00000000f03e7000                                     
x4 : 00000000f03e7000 x5 : 000000007dbff608                                     
x6 : 0000000000000030 x7 : 000000007dbff62d                                     
x8 : 000000007ff9f74d x9 : 0000000000000004                                     
x10: 0000000000200000 x11: 00000000000186a0                                     
x12: 000000000001869f x13: 0000000000000021                                     
x14: 0000000000000010 x15: 000000007dbff626                                     
x16: 0000000000200000 x17: 0000000000000000                                     
x18: 000000007dbffde0 x19: 000000007df1f6b0                                     
x20: 000000007df1f6b0 x21: 000000007ffa430c                                     
x22: 000000007ff99c52 x23: 0000000000000002                                     
x24: 000000007ffce5c8 x25: 0000000000000000                                     
x26: 0000000000000000 x27: 0000000000000000                                     
x28: 0000000000000000 x29: 000000007dbffb00                                     
Code: ffffffff ffffffff ffffffff ffffffff (ffffffff)                            
Resetting CPU ...                                                                       
### ERROR ### Please RESET the board ###                                       
```

通过dts来配置引脚电压，这个feat之前是我做的，所以这个问题的debug也就交到了我这边。

# 问题分析

这个问题比较奇怪，我首先有这么几点疑惑：

1. 触发这个问题时，启动方式是nandflash，为什么会调用到gmac？
2. 为什么其他模块的引脚在配置电压时，可以配置成功，且不会造成这个错误？

这种问题从现象上不好摸清规律，找不到切入点，好在uboot在异常发生时dump出了异常现场，先尝试从
异常现场入手

# 定位经过

根据异常现场的lr寄存器值：000000000103fe74，lr是触发异常的函数跳转前的下一条指令的地址.
将这个地址拿到uboot根目录下的System.map中查找:

```
00000000103fd7c T mmc_dump_capabilities
000000000103fd80 T mmc_get_op_cond
000000000103fe2c T mmc_start_init
000000000103feb8 T mmc_init
000000000103ff94 T mmc_set_dsr
000000000103ffa4 T mmc_initialize
000000000103fff4 t mmc_blk_probe
0000000001040010 T dm_mmc_set_ios
```

可以看到103fe74这个地址，处于**mmc_start_init**和**mmc_init**这俩函数之间。
为了更具体的定位到某一行，可以执行objdump反汇编，从反汇编结果中查找：

```
103fe60:	f00001e0 	adrp	x0, 107e000 <hex_asc+0x427>
103fe64:	910c3000 	add	x0, x0, #0x30c
103fe68:	94009ea3 	bl	10678f4 <printf>
103fe6c:	aa1303e0 	mov	x0, x19
103fe70:	940000af 	bl	104012c <mmc_deferred_probe>
103fe74:	aa1303e0 	mov	x0, x19
103fe78:	9400008c 	bl	10400a8 <mmc_getcd>
103fe7c:	35000120 	cbnz	w0, 103fea0 <mmc_start_init+0x74>
103fe80:	b9001a7f 	str	wzr, [x19, #24]
103fe84:	f00001e0 	adrp	x0, 107e000 <hex_asc+0x427>
```

可以看出，异常触发的位置，就在mmc_deferred_probe函数中：

```
int dm_mmc_deferred_probe(struct udevice *dev)
{
	struct dm_mmc_ops *ops = mmc_get_ops(dev);
    printf("ops->deferred_probe:%p\n", (void*)ops->deferred_probe);
	if (ops->deferred_probe)
		return ops->deferred_probe(dev);

	return 0;
}

int mmc_deferred_probe(struct mmc *mmc)
{
    printf("_finc_:%s line:%d \n", __func__, __LINE__);
	return dm_mmc_deferred_probe(mmc->dev);
}
```

在这两个函数中加打印，这俩个函数很简单，而且dm_mmc_deferred_probe中有一个对ops中一个函数指针的访问，很大概率是这里的问题。
加入打印后，触发异常现场，实测结果是：

```
_finc_:mmc_deferred_probe line:172                                              
ops->deferred_probe:0000000000200000                                            
```

作为对比，我将gmac的dts配置里的电压配置那一行去掉，恢复正常启动，再看这里的打印，deferred_probe的值为0。

异常情况下，deferred_probe指向的地址200000，已经超出了uboot链接地址的范围。

ops成员，一般在各个mmc的驱动中，用static定义，或者全局定义，所以应该处于data段。
在uboot代码中，全局搜索deferred_probe:

```
const struct dm_mmc_ops sdhci_ops = {
	.send_cmd	= sdhci_send_command,
	.set_ios	= sdhci_set_ios,
	.get_cd		= sdhci_get_cd,
	.deferred_probe	= sdhci_deferred_probe,
#ifdef MMC_SUPPORTS_TUNING
	.execute_tuning	= sdhci_execute_tuning,
#endif
};
```

这个问题也就较为明朗了，data段中某块区域被别的位置踩了内存。

我又将ops的地址打印出来，结果为7ffd7588这个地址，在system.map中，这个地址是找不到的，uboot会在运行时做重定位
relocate旧的global_data到新的global_data的空间上，并且修改relocate之后全局变量的label。

基础知识回顾：
在执行一个C语言程序时，此程序将拥有唯一的“内存四区”–堆区，栈区，全局区，代码区。

其中，栈区：由编译器自动分配，存放函数的形参，局部变量等，函数执行完毕时自动释放。

堆区：程序员手动分配释放（常见malloc,free等函数涉及）。

全局区：存放全局变量和（static）静态变量，里面细分有一个常量区，字符串常量和其他常量也存放在此。该区域在程序结束后由操作系统释放，

补充：全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域， 未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。

代码区：存放程序执行代码的一块内存区域、里面是二进制的代码、内存区域通常属于只读, 某些架构也允许代码段为可写，其实就是存放代码框架、或者说函数体、代码体的地方。

那么uboot的上述内存图如何对应C的内存四区呢？全局区如何构成？

代码区=start.o+*(.text)

全局区 = *(.rodata*)+*(.data)+*(.u_boot_cmd)+*(.rel*)+*(.dynsym)+*(.mmutable)+*(.bss) 

或者

全局区 = *(.rodata*)+*(.data)+空+*(.bss) 

一开始我的思路就是，找到ops的地址，以及其附近地址，所对应的relocate前的地址，这就可以在system.map里面找到这些地址对应的符号。也就知道是谁将这个地址给覆盖了。

但是我简单学了一下relocate流程，发现有些看不懂，所以还是想了其他办法。
方法1：通过仿真器，直接打上watchpoint，可以在代码修改ops里deferred_probe时停下来。
方法2：由于触发条件，是pinctrl对电压的配置，可以到这一块代码附近找一找可疑的地方。

由于pinctrl的代码就是我在负责，所以比较熟悉，经过consumer或者of模块的调用，底层的这一函数会被回调：

```
static unsigned int xxx_pins_param[ARRAY_SIZE(ts_tx5336_pins)];
static unsigned int xxxx_pins_value[ARRAY_SIZE(ts_tx5336_pins)];

static int xxxxx_pinconf_set(struct udevice *dev, unsigned pin_selector,
			       unsigned param, unsigned argument)
	xxx_pins_param[pin_selector] |= BIT(param);
	if (argument)
		xxxx_pins_value[pin_selector] |= BIT(param);
	else
		xxxx_pins_value[pin_selector] &= ~BIT(param);
```

这两个数组是静态定义的，且数组size只有8个字节。静态定义的变量也会处于data区，所以问题很可能就是它被越界访问了。

在运行时，将pin_selector打印出来，发现gmac的那几个pin对应的pin_selector值是60多，肯定是越界了。
我将这俩数组的地址打印出来，以及它们在map文件中的地址，最终汇总了一个表格：

symb reloc后 reloc前
sdhci_ops 7ffd7588 - 106f780
pins_param 7ffd752c - 10b152c
value 7ffd7550 - 10b1550

7ffd7550与7ffd7588之间的距离只有0x38，即56个字节。
临时的解决方法是将ts_tx5336_pins这个数组的大小指定为PIN_MAX值了，并且将xxxxx_pinconf_set函数中对xxx_pins_param以及xxxx_pins_value这俩数组的赋值取消掉。再次启动，uboot就通了。