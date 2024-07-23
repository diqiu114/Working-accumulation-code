# idf安装

乐鑫插件走的是vscode控制台，用的是vscode的代理，当没有手动设置vscode的代理时，vscode代理继承自系统环境变量，当选择github源时就需要走代理，然后最好python用国内清华的源，并添加ssl信任，idf会需要python环境，防止python这里出问题

换源方式：

找到pip.ini文件，添加

```
[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple
[install]
trusted-host = pypi.tuna.tsinghua.edu.cn
```



在安装idf过程中，取消安装后，再次打开vscode时，idf的插件打开时，会卡在获取版本信息这里，解决方式：

找到vscode设置配置文件setting.json，比如：

```
C:\Users\YZQ\AppData\Roaming\Code\User\settings.json
```

删除下面这两项：

    "http.proxySupport": "on",
    "http.proxyStrictSSL": false,



## 安装好后

进入工程，需要选择好芯片型号，然后需要选择调试方式：

这个步骤，idf会配置一些东西，让后续调试什么的能和芯片配得上

注意，像s3这种能够内部继承jtag接口的，他使用openOCD调试，这里如果调试方式不选jtag，那么通过OpenOcd调试时，会显示打不开OpenOcd服务

## 基于ubuntu 22.04下烧录问题：

问题点，提示：

```
A fatal error occurred: Could not open /dev/ttyUSB0, the port is busy or doesn't exist.
```

解决办法：

原因：
只有root用户和属于dialout组的用户会有读写权限

解决：
方法一：
该方法重启就会失效

```
sudo chmod -R 777 /dev/ttyUSB0
```

方法二：
永久性方案：
把自己的用户加入到dialout组：

```
sudo usermod -aG dialout user	//user替换为自己的用户名
reboot							//必须要重启一下才会生效
```

————————————————
版权声明：本文为CSDN博主「JavonPeng」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/p1279030826/article/details/111691205



# idf的配置

## 配置顺序

1. 复位插件中的各种
2. 开始配置
3. 选择合适的release
4. 配置合适的路径，注意：路径不要太深，不要带中文，不要有空格
5. 开始下载，等待安装

## 常见错误
1. 安装release 4.4.2版本时，是不需要单独下载python的，他自己会配置，但是在安装过程中，
    只要进行到python环境配置的时候，就会报错，后面发现是报错有提示，这个提示输出信息比较前，
    的位置，一直没有发现，
    此错为：pip的版本太低
    解决方法为：根据输出信息给的提示对pip进行升级就可以了
2. 最后配置python环境错误：
  1. 可能是挂了代理软件的原因以前也遇到过，挂了代理软件后就不能pip好像有冲突

## 工程转移后一开始编译就出错

这是因为build文件夹中有原先的信息，将此文件夹删除重新编译即可





# 基于esp32idf的学习

## 一些错误

1. gpio的配置放在临界区进行的话，会造成系统错误反复重启



# ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）

作者：矜辰所致

- 2022-09-27

  江苏

- 本文字数：4894 字

  阅读完需：约 16 分钟

![ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）](https://static001.geekbang.org/infoq/8e/8e47609aa0b145080e7e8c7098cda59e.png)

```
在我们前面 ESP32-C3 的教程中，从基本的外设，到wifi，到最后使用MQTT连接云平台完成了一个简单的项目，我们已经掌握了ESP32-C3 的大部分功能了。但是作为一款蓝牙芯片，蓝牙的使用是必不可少的，今天我们就开始对 ESP32-C3 蓝牙的使用进行学习测试。 蓝牙部分已经不敢叫教学了，为了搞清楚ESP-IDF的那些示例程序到底是关于什么内容，因为自己也是边学习边测试花了大量时间补充蓝牙的基本知识，希望小伙伴指出不足之处！...更新说明，ESP32-C3只支持BLE                     
```

复制代码



# 前言

从本文开始我们来进行 ESP32-C3 的蓝牙的学习测试。



> ESP32-C3 学习 蓝牙 篇系列博文连接：
>
> 自己画一块 ESP32-C3 的开发板（第一次使用立创 EDA）（PCB 到手）
>
> https://xie.infoq.cn/article/30387388381a0d915b2494f91
>
> 
>
> 开发环境是乐鑫官方的 ESP-IDF， 基于 VScode 插件搭建好的：
>
> ESP32-C3 VScode 开发环境搭建（基于乐鑫官方 ESP-IDF——Windows 和 Ubuntu 双环境）
>
> https://xie.infoq.cn/article/5b639e112cabba00cc1b8941a



首先我们来看看 ESP32-C3 的官方关于关于蓝牙部分的基本介绍：



![img](https://static001.geekbang.org/infoq/de/dea68ed2b0e6d75757e30bbc5b3bc8e8.png)



ESP32-C3 增加了对 Bluetooth LE 5.0 协议的支持，包含 Coded PHY (Long Range) 和扩展广播 (extended advertisement) 功能。它通过引入 FEC 编解码等技术，虽然增加了数据冗余度，但是大幅度增加了设备通信距离（通常为 100 米）。此外，ESP32-C3 还支持蓝牙 Mesh (Bluetooth Mesh) 协议，这使它成为了控制本地网络设备，以及直接与其他 Bluetooth LE 5.0 传感器设备进行通信的强大候选设备之一。



但是说到蓝牙学习，查看一下官方的文档介绍：[乐鑫官方ESP32-C3 蓝牙API介绍](https://xie.infoq.cn/link?target=https%3A%2F%2Fdocs.espressif.com%2Fprojects%2Fesp-idf%2Fzh_CN%2Flatest%2Fesp32c3%2Fapi-reference%2Fbluetooth%2Findex.html)



![img](https://static001.geekbang.org/infoq/42/42472ac10f121a1e55f4a232e9ae3280.png)



这么多蓝牙 API，难道都得学会了怎么用？



所以这里就得明白这些示例的含义，然后学会了哪些 API 的使用，才能做基本的应用！



用起来才是学习的最终目的嘛！



想着我们可以先看看 IDF 中蓝牙的例子有哪些，一看吓一跳，我的个天（截了 2 个屏幕还不够放的……）：



![img](https://static001.geekbang.org/infoq/41/41bd89313f4db4fec5c558f205e77296.png)



反正看完，头有点大，蓝牙协议的认识，还是当时学习 NRF52832 的时候认真了解过一段时间，但是当时还是因为 NRF52832 在一些项目上已经没有了价格优势，所以也暂停了一段时间，刚接触个蓝牙 5.0 的框架，还没结合实际代码深入了解。



虽然每个例子都有说明是干什么用的，如下图：



![img](https://static001.geekbang.org/infoq/86/862ee011de14af25c451f5f204ab4f38.png)



但是如果连基本的蓝牙协议专有名词都不知道，还是无法明白！



因为专栏的目的是为了能够做一些小的项目，所以还是参考了多方面的资料，就本文的目的，就是争取把 ESP32-C3 使用的 ESP-IDF 中 蓝牙的这些 示例程序是干什么了解清楚 。有了基本的了解，我们才知道去学习哪个示例，可以用来干什么！



所以本文应该会不定期的根据自己慢慢学习测试总结的结果进行更新维护！

# 1、蓝牙基本介绍

介绍这一块我就不班门弄斧了，把一些看到的觉得好的文章拿过来推荐给大家！因为蓝牙这一块的理论，专有名词不是一句两句就能说得清楚的：



在我的另一篇博文中，有一些关于蓝牙的基本介绍：



蓝牙 5.0 简介、nRF52832 BLE 样例工程框架及 main 函数初始化流程简析

https://xie.infoq.cn/article/1deef0aebd522b1ce7a725388



推荐几篇很好的文章：



[ESP32 蓝牙开发：原理简述](https://xie.infoq.cn/link?target=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F391666757)



[蓝牙核心技术了解（蓝牙协议、架构、硬件和软件笔记）](https://xie.infoq.cn/link?target=https%3A%2F%2Fwww.cnblogs.com%2Fshaobojiao%2Fp%2F7883330.html)



[三种蓝牙架构实现方案（蓝牙协议栈方案） ](https://xie.infoq.cn/link?target=https%3A%2F%2Fwww.cnblogs.com%2Fiini%2Fp%2F8834970.html)



[现在最火的蓝牙5、蓝牙低功耗和经典蓝牙，你知道他们的区别吗？](https://xie.infoq.cn/link?target=http%3A%2F%2Fwww.iotworld.com.cn%2Fhtml%2FNews%2F201908%2Fe147e35b1a800443.shtml)



还有前人写的 ESP32 的蓝牙博文：



[ESP32学习笔记十七之蓝牙通信-Bluetooth](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fzym326975%2Farticle%2Fdetails%2F96975472%3Futm_medium%3Ddistribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0.pc_relevant_paycolumn_v3%26spm%3D1001.2101.3001.4242.1%26utm_relevant_index%3D3)



[esp32系列(5)：esp32 蓝牙架构学习](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Flum250%2Farticle%2Fdetails%2F123012522%3Futm_term%3Desp-idf%20%E8%93%9D%E7%89%99%E6%9E%B6%E6%9E%84%26utm_medium%3Ddistribute.pc_aggpage_search_result.none-task-blog-2~all~sobaiduweb~default-0-123012522%26spm%3D3001.4430)



**这里总结性的说明几个重要的点：**

## 1.1  经典蓝牙（BT） 和 低功耗蓝牙（BLE）

蓝牙分为 经典蓝牙(Classic Bluetooth) **BT** 和 蓝牙低功耗(Bluetooth Low Energy) **BLE**。



也可以称为 蓝牙 BR/EDR 和 BLE：



![img](https://static001.geekbang.org/infoq/8f/8fb2fd7b9024f31c7c5a8665b09afb18.png)



如果要深入了解 经典蓝牙 与 蓝牙 BLE 的区别，对于本文下面章节《1.3 蓝牙协议栈》的内容也得有一定的了解，或者在上面的推荐文章中，已经掌握了基本的一些理论基础：



比较蓝牙 BR / EDR 和 BLE 之间的异同。一个好的起点是协议的物理层(PHY)。PHY 包含用于调制和解调模拟信号并将其转换为数字符号的电路。BR / EDR 和 BLE 不同的 PHY 的四个特性包括信道方案，功耗，延迟和吞吐量。



- 信道蓝牙 BR / EDR 和 BLE 都在 2.4GHz ISM 频段内通信，但它们划分频段的信道数不同。蓝牙 BR / EDR 将频段划分为间隔 1 MHz 的 79 个频道。BLE 采用更简单的发射器和接收器，因此它将频带划分为间隔 2 MHz 的 40 个通道。
- 功率 BLE 低功耗蓝牙的特点就是功耗低，至于功耗的具体数值，随着新版本的不停发布，这里就不给具体数值。
- 延迟 BLE 优于蓝牙 BR / EDR 的另一个特点是延迟。蓝牙 BR / EDR 大约需要 100 ms 才能准备好发送数据。从发射器接收数据到接收器可用数据时，还有 100 毫秒的延迟。在某些情况下，这会导致相当明显的延迟。它还会导致更高的功耗，因为发送数据所需的额外时间会导致更多的电池消耗。BLE 提供更低的延迟，只需 3 ms 即可准备发送数据。此外，从发送器接收数据到接收器可用时的等待时间仅为 6 ms。这样可以更快地发送数据并节省电力。
- 吞吐量终于有了一个经典蓝牙的优势之处，相对来说，低功耗蓝牙的吞吐量肯定会小于经典蓝牙的。但是到了蓝牙 5.0 以后，BLE 的速度有了大量提升……



**应用领域：**



**经典蓝牙：**1.传声音蓝牙耳机、蓝牙音箱。移动的如耳机、便携音箱都是基于经典蓝牙协议的。



2.传大量数据例如某些工控场景，使用 Android 或 Linux 主控，外挂蓝牙遥控设备的，可以使用经典蓝牙里的 SPP 协议，当作一个无线串口使用。速度比 BLE 传输快多了。这里要注意的是，iPhone 没有开放



**蓝牙 BLE**：耗电低，数据量小，如遥控类(鼠标、键盘)，传感设备(心跳带、血压计、温度传感器、共享单车锁、智能锁、防丢器、室内定位)1、健康医疗用品 2、定位应用 3、近距离数据采集 4、智能家居应用 5、移动扩展设备 6、汽车电子设备



**双模蓝牙:**双模蓝牙是包含经典蓝牙协议，也包含 BLE 蓝牙协议的双协议模块：如智能电视遥控器、降噪耳机等。很多智能电视配的遥控器带有语音识别，需要用经典蓝牙才能传输声音。如果做复杂的按键，例如原本键盘表上没有的功能，经典蓝牙的 HID 按键协议就不行了，得用 BLE 做私有协议。很多降噪耳机上通过 APP 来调节降噪效果，也是通过 BLE 来实现的私有通信协议。



在 ESP32-C3 芯片上，只支持 BLE。



关于这个问题，当初我说两者都支持，因为 ESP-IDF 中有经典蓝牙和 BLE 的示例都有，而且没有深入的测试了解，经过留言区小伙伴的提醒，查阅了相关的资料，确定 ESP32-C3，只支持 BLE。



官方的介绍芯片时是说，ESP32-C3 支持 2.4 GHz Wi-Fi 和 **Bluetooth 5 (LE)**，在《ESP32-C3 系列芯片技术规格书》中也只提到，ESP32-C3 具有 低功耗蓝牙子系统，支持 Bluetooth 5 和 Bluetooth mesh。其中还有一张图也可以说明问题：



![img](https://static001.geekbang.org/infoq/ff/ff55d68400f2cf8b55417c4e5b8bcf69.png)

## 1.2 蓝牙 Mesh 和 蓝牙 BLE

蓝牙 Mesh 是一种  网络技术。蓝牙 Mesh 网络依赖于 蓝牙 BLE。



低功耗蓝牙技术是蓝牙 Mesh 使用的无线通信协议栈。



蓝牙 Mesh 基于蓝牙 BLE 低功耗广播



蓝牙 Mesh 采用蓝牙低功耗广播的方式就行信息发送和接受，将信息从网络当中的某一个节点转发至目的节点，在蓝牙 Mesh 组网中，这种广播模式也称为网络泛洪。



**在 ESP32-C3 芯片上，ESP-IDF 提供了 蓝牙 Mesh 网络的 API，可以直接应用。**

## 1.3 蓝牙协议栈

蓝牙的协议栈我在另一篇博文也介绍过，因为进一步的学习让自己对蓝牙的知识更进一步，这里再来说明一次，还是以 BLE 协议为主，因为在今后的应用中 BLE 应该是用得最多的：



![img](https://static001.geekbang.org/infoq/ee/ee836f2e74c91029f3a69980a2e6a23d.png)



这里我用一张表格总结一下，看起来更加的直观：



![img](https://static001.geekbang.org/infoq/c0/c0f8dae42c7aef5abbf9700c8c4e2234.png)

## 1.4 蓝牙芯片方案的实现

结合蓝牙协议栈的内容，配合上面的推荐文章《三种蓝牙架构实现方案（蓝牙协议栈方案）》，我们可以来说明一下，一般厂家蓝牙方案是怎么设计的：



对于 BR/EDR 蓝牙设备类型，Controller 通常包含 无线电处理、基带、链路管理、和可选择的 HCI 接口层；对应 LE Controller 主要包含 LE PHY、链路层、和可选择的 HCI；



如果把 BR/EDR Controller 和 LE Controller 设 计到一个 Controller，就是我们常说的双模蓝牙。



如下图：



![img](https://static001.geekbang.org/infoq/65/659b7c4fcc8bf15c1e427fb4582cbaec.png)



在单芯片方案中，Controller 和 Host，profiles，和应用层都在同一片芯片中；在网络控制器模式中，Host 和 Controller 是在一起运行的，但是应用 和 profiles 在另外一个器件上，比如 PC 或者其他微控制器，可以通过 UART， USB 进行操作；在双芯片模式中，Controller 运行在一个控制器，而应用层，profiles 和 Host 是运行在另外一个控制器上。



对于我们的 ESP32-C3 芯片而言，我认为是下图这种（有错误清指出！！）



![img](https://static001.geekbang.org/infoq/2b/2b8ad018cf176ebf449848305e0f85c2.png)



即便上面的推荐资料全部看完了，也有不少同学还是会犯迷糊，概念多，协议多，体现到代码上到底哪些是我们需要学习使用修改的呢？  这个先别急，我们再来把 ESP-IDF 蓝牙框架了解一下！

# 2、ESP32-C3 ESP-IDF 蓝牙框架

### 相关的api

1. BT COMMON
   - [Bluetooth DEFINE](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_bt_defs.html)
   - [Bluetooth MAIN](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_bt_main.html)
   - [Bluetooth DEVICE](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_bt_device.html)
2. BT LE
   - [BLE GAP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_gap_ble.html)
   - [BLE GATT DEFINE](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_gatt_defs.html)
   - [BLE GATT SERVER](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_gatts.html)
   - [BLE GATT CLIENT](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_gattc.html)
   - [BLE BLUFI](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_blufi.html)
3. CLASSIC BT
   - [BT GAP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_gap_bt.html)
   - [BT A2DP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_a2dp.html)
   - [BT AVRC](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_avrc.html)
   - [BT SPP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_spp.html)
   - [BT HFP Define](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_hf_defs.html)
   - [BT HFP Client](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_hf_client.html)
   - [BT HFP AG](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_hf_ag.html)
   - [BT HID DEVICE](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_hidd.html)
   - [BT L2CAP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_l2cap_bt.html)
   - [BT SDP](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp_sdp.html)
4. Controller && VHCI
   - [Application Example](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/controller_vhci.html#application-example)
   - [API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/controller_vhci.html#api-reference)
5. ESP-BLE-MESH
   - [Application Examples and Demos](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp-ble-mesh.html#application-examples-and-demos)
   - [API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp-ble-mesh.html#api-reference)
   - [ESP-BLE-MESH Definitions](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp-ble-mesh.html#esp-ble-mesh-definitions)
   - [ESP-BLE-MESH Core API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp-ble-mesh.html#esp-ble-mesh-core-api-reference)
   - [ESP-BLE-MESH Models API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/esp-ble-mesh.html#esp-ble-mesh-models-api-reference)
6. NimBLE-based host APIs
   - [Overview](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/nimble/index.html#overview)
   - [Architecture](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/nimble/index.html#architecture)
   - [Threading Model](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/nimble/index.html#threading-model)
   - [Programming Sequence](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/nimble/index.html#programming-sequence)
   - [API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/bluetooth/nimble/index.html#api-reference)

回到我们需要使用的 ESP-IDF 本身，官方的对于蓝牙 API 的说明如下：



![img](https://static001.geekbang.org/infoq/f5/f562a12dc43206a6e57c4be664cb3f45.png)



我们上文已经更新了说明，ESP32-C3 只支持 BLE，虽然 ESP-IDF 有传统蓝牙和 BLE，但是在 ESP32-C3 上面只能运行与 BLE 有关的示例。



经过上面那么多理论知识的洗礼，我们再回头看看 ESP-IDF 蓝牙 API：



![img](https://static001.geekbang.org/infoq/f4/f455333669c4972f6c30008052246e8c.png)



整体的结构我们已经差不多能够明白了，那么我们从 ESP-IDF Examples 的例程来看一看实际的例程分别是关于什么的。

## 2.1 基于 Bluedroid 的示例

**第一部分 Bluedroid 堆栈中的 ble 部分：**



![img](https://static001.geekbang.org/infoq/b4/b4ee424ff26ca19134a387db11737803.png)



我们前面说过，GATT 用来规范 attribute 中的数据内容，并运用 group（分组）的概念对 attribute 进行分类管理。为主从设备交互数据提供 Profile、Service、Characteristic 等概念的抽象、管理。所以在这个示例程序中，关于 GATT 的示例是非常多的。



除此之外，包括我们经常能见到的蓝牙串口透传，使用的就是 SPP 协议（zq：Serial Port Profile串行端口规范）。



蓝牙 Ibeacon 模式，是作为信标用于蓝牙定位的一种协议。



鼠标键盘，其他外设 HID 设备的延时，也提供了对应的例子。



**第二部分 ble_50 部分：**



![img](https://static001.geekbang.org/infoq/b2/b2149d10a8b05f419ca6596aa31a1bfc.png)



对于示例中的这部分，居然没有说明，这里也就不过多解释。



**第三部分 经典蓝牙 classic_bt 部分：**



![img](https://static001.geekbang.org/infoq/29/295c7a494dcea7dcdf3747f0a973e708.png)



我们前面介绍过，经典蓝牙与蓝牙 ble 的应用领域的时候介绍过：经典蓝牙的应用领域有蓝牙耳机、蓝牙音箱，那么在 ESP-IDF 经典蓝牙部分，这两个部分的示例代码都提供了！



还有 SPP 协议，蓝牙串口相关的，接收端，发送端，都单独的有自己的使用示例；



在最后可以使用 hfp_ag 和 hfp_hf 示例与音频网关（AG）设备（例如智能手机）通信。



**第四部分 coex 部分：**



![img](https://static001.geekbang.org/infoq/df/dff59fc1cdbdb9b7c905038f93c85472.png)



经典蓝牙和 BLE 共存，在前面我们提到过，如果把 BR/EDR Controller 和 LE Controller 设 计到一个 Controller，就能实现双模蓝牙，我们也说过 ESP32-C3 是有两种类型的 Controller 。

## 2.2 基于 ESP-BLE-MESH 的示例

上面介绍完成，到了 esp_ble_mesh 部分，我们还是一个一个看下去：



![img](https://static001.geekbang.org/infoq/c1/c1217de6850051f04d472d30af4d33a5.png)



乐鑫的 IDF 中，居然就直接有和阿里精灵连接的例子。

## 2.3 基于 hci 的示例

![img](https://static001.geekbang.org/infoq/9d/9d4293a7814833c80887eeecbe4138e6.png)



前面介绍过，HCI 主要用于两个 MCU 实现 BLE 协议栈的场合，规范两者之间的通讯协议和命令。Controller  和 HCI 相关的东西，现在不太好说明！

## 2.4 基于 Apache NimBLE 的示例

Apache NimBLE 的堆栈仅支持 BLE，所以这部分也是和 BLE 有关的示例：



![img](https://static001.geekbang.org/infoq/00/00df267a10da762a1289efd1f39fb75c.png)



对于这部分的说明，ESP-IDF 给出的 readme 都是比较详细的，或许是因为在代码占用和运行时，NimBLE 对内存的要求较低？

## 2.5 其他和蓝牙有关的示例

![img](https://static001.geekbang.org/infoq/09/091e7c79453518219e4d4b0c1369a097.png)



The Human Interface Device (HID)定义了蓝牙在人机接口设备中的协议、特征和使用规程。典型的应用包括蓝牙鼠标、蓝牙键盘、蓝牙游戏手柄等。该协议改编自 USB HID Protocol。蓝牙 HID 是属于蓝牙协议里面的一个 profile（应用层）。

# 结语

至此，对于 ESP32-C3 来说， ESP-IDF 中所有的蓝牙示例简单来说是干什么的都过了一遍，对于一块知识的学习，还是得先把基础打好，像蓝牙协议这么多专有名词，专业术语的知识来说，还是很有必要花足够的时间去对基础知识进行学习！



这篇文章是 ESP32-C3 蓝牙篇的开始，只是对我们将要对面的东西做了一个介绍，让自己让大家认识一下。



对于 ESP-IDF 使用来说，蓝牙篇章入门的资料少之又少，我学习查找资料几天，甚至都没有找到过确实的介绍 ESP-IDF 中示例介绍的文章 = =！ 所以期间头很大，自己对蓝牙协议的理解也没那么深，所以在写博文的时候举步维艰，目前基本上没办法写出自己的理解，质量还请大家理解。文中的错误与不足在今后我会随时更新。同时希望有懂蓝牙的大佬多多指点。



ESP32-C3 蓝牙接下来的学习更新可能会没以前那么快，因为所有的示例，我都会尽量去跑一跑测试下，然后用来干嘛的？怎么用的？有什么意义？尽量都搞清楚了才会更新，希望大家理解！谢谢！

# ESP32-C3 学习测试 蓝牙 篇（二、蓝牙调试 APP、开发板手机连接初体验）

作者：矜辰所致

- 2022-09-29

  江苏

- 本文字数：1675 字

  阅读完需：约 5 分钟

![ESP32-C3 学习测试 蓝牙 篇（二、蓝牙调试APP、开发板手机连接初体验）](https://static001.geekbang.org/infoq/3b/3b7559623426010f8b26f2acf3ca8d59.jpeg)

```
等了好久终于等到今天，盼了好久终于把蓝牙测试 = =！ESP32-C3 专栏好久没更新了，这次抽点时间把蓝牙的准备工作做完。
```

复制代码



# 前言

距离上一次玩 ESP32-C3 的板子也有一段时间了，其实都是因为时间安排不过来，最近挤出了一点时间，看了一点蓝牙的资料，想着至少也要做个入门测试，让手机和开发板连接起来！



> ESP32-C3 学习 蓝牙 篇系列博文连接：
>
> 自己画一块 ESP32-C3 的开发板（第一次使用立创 EDA）（PCB 到手）
>
> https://xie.infoq.cn/article/30387388381a0d915b2494f91
>
> 
>
> 开发环境是乐鑫官方的 ESP-IDF， 基于 VScode 插件搭建好的：
>
> ESP32-C3 VScode 开发环境搭建（基于乐鑫官方 ESP-IDF——Windows 和 Ubuntu 双环境）
>
> https://xie.infoq.cn/article/5b639e112cabba00cc1b8941a
>
> 
>
> 蓝牙篇系列相关博文：
>
> ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）
>
> https://xie.infoq.cn/article/efbe5651b35c9d54c69bc0ab2

# 1、蓝牙手机调试工具

首先要和开发板的蓝牙连接，得找个合适的蓝牙调试工具，网上查了查，下面我一一介绍：



**nRF Connect：**



一看名字就知道是是 Nordic 官方开发，与他们 PC 端的名字一样。



**BLE 调试助手**：



南京沁恒微电子开发的 app，这个公司最火的还是他们的 CH340 USB 转串口芯片，不过现在也有了 RISC-V 内核的 CH32V 系列、蓝牙 5.1 等系列的 MCU。



**LightBlue：**



国外 Punch Through 开发的，我看一些视频中有人用过。



最初我是准备下载 nRF Connect 的，因为用过 Nordic 的 nRF52832 芯片，然后使用过他们桌面版本的，所以想着下载一下，但是使用自己的安卓手机到应用商店没有找到= =！同样的，LightBlue 在应用商店也找不到，只能找到 BLE 调试助手，没什么可犹豫的就用这个了，下载好打开界面如下：



![img](https://static001.geekbang.org/infoq/27/27ee7d4fc3a36e67408a248671e43a56.png)



不过一会我就找到一个 iphone，在苹果应用商店直接把 nRF Connect 也下载了，但是后面看到 LightBlue 的评价数量比 nRF Connect 多，于是把 LightBlue 也下载了，他们界面如下（左边 nRF Connect，右边 LightBlue ）：



![img](https://static001.geekbang.org/infoq/0d/0d2e8c9cdf796585902ea63bfdabc7ce.png)



那么好了，调试 app 都已经准备完毕，以后就使用这几个 APP，至于用哪个，看心情吧，现在没有深入的体会，等以后熟悉了再来谈谈。

# 2、ESP-IDF 中示例的选择

对于初次接触蓝牙的小伙伴来说，面对 ESP-IDF 中那么多示例，也不知该如何选择。



这里讲一讲，作为一个入门者，我是如何选择例程的？



首先，我在蓝牙篇的第一篇文章中，简单介绍了一下蓝牙的协议栈，对于博主的智能家居领域，跟符合 ble 应用场景，而且现在 ble 的应用广泛，很火，肯定是先从 ble 入手。查看了一些资料，了解到对于应用开发者来说，需要用到的主要是 GAT、GATT 和 ATT，那么就得找与这几个专有名词相关的示例。



纵观全局，也只有这个地方有且只有与 GATT 有关的示例：



![img](https://static001.geekbang.org/infoq/1a/1ae7743c044a1854f289440bab27d972.png)



其中要了解 ：GATT Client 是主机，比如手机，蓝牙网关。GATT server 是从机，比如传感器。



通过以上说明，我们把范围确定在了 Ble 示例中的，GATT server 相关的示例。



其次，上一篇文章中我还花了大量时间去查看每个工程的示例的说明，结合注释选择了 2 个比较合适的，如下图的蓝色圈内的示例：



![img](https://static001.geekbang.org/infoq/1f/1f6a766da26a9abf45a65f4a6f3eddce.png)



还是依靠着自己曾经的付出，找到了我们入门需要的示例。

# 3、ESP32-C3 BLE 与手机连接初探

选择好了示例，那么就到了我们熟悉的流程，选择示例新建工程：



![img](https://static001.geekbang.org/infoq/97/9769d8ef571871c6abdd62eb236f5e21.png)



记住，新建工程以后第一时间修改芯片型号！否则容易出莫名的问题。



![img](https://static001.geekbang.org/infoq/e0/e0e9737a71d9674cae4f07cdb3f9bf65.png)



然后代码随便看一看，不需要看实现方式，因为设备肯定有个名称，第一次的测试我习惯就是改个厉害的名称！ 如下图：



![img](https://static001.geekbang.org/infoq/c8/c8a336e5c633856be7ad3af54d799ad2.png)



什么都不管，直接编译烧录……（编译时间会比以前文章将的示例啊，工程都久一点= =！）



。。。。。。



烧录结束正常的 LOG 输出，这里就不放上电启动的图片了，反正现在也看不懂，我们用手机扫描一下看看：



![img](https://static001.geekbang.org/infoq/40/40aee78c82ec1321c4a2d3365c4b6abe.png)



成功！ 不管怎样，我们已经可以和手机通讯了~ ~

# 结语

本文我们把蓝牙学习测试需要的手机 APP 准备完毕，找到并成功测试了 ESP32-C3 跑 ble 协议和手机连接的功能，看上去还可以实现消息传递（因为我们还没有进行深入学习，实际上确实是可以传递消息的）。



虽然没有做很深入的分析讲解，但是我们有了一个好的开始，那么已经就成功了一半了！



接下来我们会去深入的理解一下 蓝牙 BLE 的 GATT，然后在此基础上进一步的了解修改示例。



今天就到这，谢谢！

发布于: 2022-09-29阅读数: 45

版权声明: 本文为 InfoQ 作者【矜辰所致】的原创文章。

原文链接:【https://xie.infoq.cn/article/a422913b3b0420b1ae7c1436d】。文章转载请联系作者。

# ESP32-C3 学习测试 蓝牙 篇（三、认识蓝牙 GATT 协议）

作者：矜辰所致

- 2022-09-29

  江苏

- 本文字数：4102 字

  阅读完需：约 13 分钟

![ESP32-C3 学习测试 蓝牙 篇（三、认识蓝牙 GATT 协议）](https://static001.geekbang.org/infoq/89/895301d51d8013cf274ecd90f5f1d95c.png)

```
磨刀不误砍柴工，本文了解一些基本的蓝牙协议基础知识... 更新概念导图部分关于 Server 和 Service 文字说明 
```

复制代码



# 前言

上一篇系列文章我们使用 ESP-IDF 中的示例 GATT server，完成了手机连接开发板的初次体验。 



虽然上文我们找到的入门的 GATT server 示例，但是对于蓝牙 GATT 概念，我们还是只停留留在 蓝牙协议栈基本框架层面的内容，对于更具体的理解我们还不知道，所以针对示例来说，我们也无从修改测试。



正所谓磨刀不误砍柴工，我们有必要先深入的学习一下 GATT 以及 GATT 相关的一些知识。



本文我们就来了解一下 蓝牙 GATT 到底是什么？同时了解下我们使用的 ESP32-C3 GATT 示例的工程的代码结构。



> ESP32-C3 学习 蓝牙 篇系列博文连接：
>
> 自己画一块 ESP32-C3 的开发板（第一次使用立创 EDA）（PCB 到手）
>
> https://xie.infoq.cn/article/30387388381a0d915b2494f91
>
> 
>
> 开发环境是乐鑫官方的 ESP-IDF， 基于 VScode 插件搭建好的：
>
> ESP32-C3 VScode 开发环境搭建（基于乐鑫官方 ESP-IDF——Windows 和 Ubuntu 双环境）
>
> https://xie.infoq.cn/article/5b639e112cabba00cc1b8941a
>
> 
>
> 蓝牙篇系列相关博文：
>
> ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）
>
> https://xie.infoq.cn/article/efbe5651b35c9d54c69bc0ab2
>
> ESP32-C3 学习测试 蓝牙 篇（二、蓝牙调试 APP、开发板手机连接初体验）
>
> https://xie.infoq.cn/article/a422913b3b0420b1ae7c1436d



------

# 一、概念导图

☆ 即便看完了很多资料，博主自己还是感觉蓝牙协议的专有名词定义有点复杂（相对其他很多物联网无线协议来说），如果不是专门从事蓝牙行业的人，即便官方有资料，对于这些专有名词专有定义也难以全部理解到位。



☆ 但是我们系列博文最终是以应用为目的，使用蓝牙最终还是使用蓝牙做一些数据的传输交互应用。所以对于专有名词暂时不用研究那么深，知道一些基本概念的的作用和意义即可。



对于基本的概念知识，查阅了很多相关的资料后多少有了一个初步的认识，对于蓝牙 GATT 来说，以应用为主所需要的了解的基本概念，主要就是 **GATT，GAP，ATT** 这几个协议，在系列博文第一篇《ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）》关于蓝牙协议的说明对于这几个协议的简单说明，如下图：

**我的理解是**：

	1. **ATT：定义了数据的结构**
	2. **GAP：用来进行广播，扫描和发起连接**
	3. **GAAT：用来管理ATT**



![img](https://static001.geekbang.org/infoq/c7/c71403d1424ff441c0150a5ef157ab08.png)





**对于我们的应用来说，蓝牙无非是用来进行数据交互，我们直接从应用说起，我们使用手机和开发板进行蓝牙通讯，对应的 手机就是 Client 设备，开发板就是 Server 设备。**



**对于我的学习来说，就是从 BLE 通信的这两种设备入手的 ：Client 和 Server。**

## GATT 的结构

对于 Client 和 Server 的通讯，先来看一张图：



![img](https://static001.geekbang.org/infoq/9e/9ecea071ed552121624c07b2fe61852c.png)



从上面的示意图可以看出，对于 GATT server 有很多分支，可想而知对于他的协议规定会有很多专有名词，**我们的应用程序也大多是对 GATT server  这些参数进行修改配置**，我总结了几张概念导图。



![img](https://static001.geekbang.org/infoq/8d/8d6823ced79c2dea8c30c3f1501c39c0.png)



图中用的是 GATT Server 后面的分支应该是 Service！！

## Service 的结构

图中用的是 Server（服务器），应该用 Service ，当初做图的时候估计还有点蒙：

#### 

![img](https://static001.geekbang.org/infoq/f5/f5f764dba335121733adbc3ef47030fc.png)



上图中虽然以 Server 作为开头，其实 Server 可组成一个叫 profile 的概念（下面概念说明会讲到 ）。

## Profile （配置）的结构

蓝牙官方文档中对于 Profile 说明图：



![img](https://static001.geekbang.org/infoq/84/847fa2827f0f742f5ae30e20844d1c05.png)

# 二、概念说明

虽然上面上了一张概念导图，但是对于里面的一些基本概念我们有必要一个一个单独说明一下。



这里推荐几篇文章，部分内容也有参考：



[ATT和GATT的概念](https://xie.infoq.cn/link?target=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F80404930)



[蓝牙【GATT】协议介绍](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fu013378580%2Farticle%2Fdetails%2F52891462)

## 2.1 名词解释

对概念导图中提到的专有名词进行单独的说明。

### Server

- Service 可以理解为一个服务，提供数据的服务，比如从机设备，但是在一个 Ble 从机中，可以有多个服务。
- Server 和 Client 通过 ATT PDU 进行交互。
- Server 通过 characteristic 对数据进行封装，每个 service 中又包含多个 characteristic 特征值。

### profile

- 如果上面说的 service 是一个蓝牙联盟定义的标准服务，也可以称其为 profile。
- profile 可以**理解为一种规范，一个标准的通信协议，它存在于从机中。**
- 蓝牙组织规定了一些标准的 profile，比如 HID/心率计/体温计/血糖仪等，都是标准蓝牙服务，因此都有相应的 profile 规格书。
- 每个从机都会有一个叫做 profile 的东西存在，不管是的自定义的 **simpleprofile**，还是标准的心率计 profile。
- 每个 profile 中会包含多个 service，每个 service 代表从机的一种能力。

### characteristic（特征）

- 上面讲到： Server 通过 characteristic 对数据进行封装，每个 service 中又包含多个 characteristic 特征值。
- ble 主从机的通信均是通过 characteristic 来实现，可以理解为一个标签，通过这个标签可以获取或者写入想要的内容。
- 一个 characteristic 包含三种条目：characteristic **声明**，characteristic 的**值**以及 characteristic 的**描述符**。
- 这 3 个条目的含义可参考上面的概念导图，这里需要说明的是它们是用 attribute 来表达的，它们每一个都是一个 attribute 。
- 
- Characteristic 是在 GATT 规范中最小的逻辑数据单元，由一个 Value 和多个描述特性的 Desciptior （描述符）组成。实际上，**在与蓝牙设备打交道，主要就是读写 Characteristic 的 value 来完成。**

### attribute（标志，象征）

- Attribute 是属于 ATT 属性层的东西，它是 ATT 层 的核心。



- **Attribute 其实就是一条一条的数据。**前面说过，**每个蓝牙设备就是用来提供服务的，而服务就是众多数据的合集，这个合集可以称为数据库，数据库里面每个条目都是一个 attribute。**

- 

- Attribute 由以下 4 部分组成：属性句柄(Attribute Handler)、属性类型(AttributeType)、属性值(Attribute Value)、属性权限(Attribute Permissions)。

  ![img](https://img-blog.csdnimg.cn/1949a16278f1403c99b4c123d9f44e14.png) 

  

- 更多详细的说明可参考：

- [蓝牙BLE： ATT协议层中属性(Attribute)](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fdaocaokafei%2Farticle%2Fdetails%2F114745007%3Fops_request_misc%3D%26request_id%3D%26biz_id%3D102%26utm_term%3D%E8%93%9D%E7%89%99Attribute%26utm_medium%3Ddistribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-114745007.142%5Ev10%5Epc_search_result_control_group%2C157%5Ev12%5Econtrol%26spm%3D1018.2226.3001.4187)

- [蓝牙属性表理解（Bluetooth Attribute Protocol / ATT ）](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fhill_guo%2Farticle%2Fdetails%2F121605863)

### UUID

- UUID（**universally uniqueidentifier，通用唯一识别码**）**是一个软件构建标准，一个合法的 UUID，一定是随机的、全球唯一的。（UUID 并不是 BLE 独有的概念）**
- 上面提到的 service 和 characteristic，都需要一个唯一的 uuid 来标识。
- UUID 是 128 bit 的。
- **蓝牙联盟采用为官方的 UUID：`0000xxxx-0000-1000-8000-00805F9B34FB`**（上面概念图和推荐博文有详细说明）

## 2.2 GATT (Generic Attribute Profile)

GATT (通用属性配置) ，它定义两个 BLE 设备通过 Service 和 Characteristic 进行通信；



GATT 就是**使用了 ATT（Attribute Protocol）协议，ATT 层定义了一个通信的基本框架，数据的基本结构，以及通信的指令，Service 和 characteristic 就是 GATT 层定义的， GATT 层用来赋予每个数据一个具体的内涵，让数据变得有结构和意义。**



前面说过 server 端提供服务，服务就是数据，而数据就是一条一条的 attribute，而 service 和 characteristic 就是数据的逻辑呈现，或者说**用户能看到的数据最终都转化为 service 和 characteristic。**



一旦两个设备建立起了连接，GATT 就开始起作用了，这里需要说明的是，GATT 连接必需先经过 GAP 协议。



GATT 连接需要特别注意的是：**GATT 连接是独占的**。也就是一个 BLE 外设同时只能被一个中心设备连接；



中心设备和外设需要双向通信的话，唯一的方式就是建立 GATT 连接。

## 2.3 GAP(Generic Access Profile)

Generic Access Profile（通用访问规范） **它在用来控制设备连接和广播，用于提供蓝牙设备的通用访问功能，包括设备发现、连接、鉴权、服务发现等等。**



GATT 是建立连接后通信规范， 而蓝牙是通过 GAP 建立通信的。



GAP 使你的设备被其他设备可见，并决定了你的设备是否可以或者怎样与合同设备进行交互。



GAP 给设备定义了若干角色，其中主要的两个是：**外围设备**（Peripheral）和**中心设备**（Central）。



- 外围设备：这一般就是非常小或者简单的低功耗设备，用来提供数据，并连接到一个更加相对强大的中心设备。例如小米手环。
- 中心设备：中心设备相对比较强大，用来连接其他外围设备。例如手机等。

## 2.4  ATT(Attribute Protocol)(属性协议)

**ATT（Attribute Protocol）属性层是 GATT 和 GAP 的基础**，它定义了 BLE 协议栈上层的数据结构和组织方式。



ATT 协议定义了两种角色：服务器角色和客户端角色。



站在蓝牙协议栈角度来看，**ATT 层定义了一个通信的基本框架，数据的基本结构，以及通信的指令**，而 GATT 层就是前文所述的 service 和 characteristic，**GATT 层用来赋予每个数据一个具体的内涵，让数据变得有结构和意义。**



GATT 是脱胎于 ATT ，ATT 是 Attribute Protocol Specification 属性规范协议，注意 ATT 是协议，而 GATT 是规范，两者不同点在于 ATT 规定了数据格式，而 GATT 则是按照 ATT 的格式将具体数据填充进去。

# 三、Client 设备连接说明

我们上面讲了很多关于蓝牙 GATT 的概念知识，我们开发板使用了 GATT server 示例后，就是一个 Server 设备，我们的手机就是 Client 设备。



当我们连接上以后，其实可以查看 Server 的信息的，为了加深对上面的概念的理解，我们使用手机连接后的图片来说明一些概念：



![img](https://static001.geekbang.org/infoq/00/00cb76d747f57504c31fce9f28952acd.png)



![img](https://static001.geekbang.org/infoq/f2/f2088c81ebc06752cde45ac38e8c19a6.png)



![img](https://static001.geekbang.org/infoq/de/de270aa276077d8d8b8487d431b429e9.png)



在上图中有一点，结合上面第一小节《一、概念导图》 中的 Profile 的结构 说明，每个 characteristic 都带有 Properties，这个 Properties 为蓝牙特征值的读写权限：





上面是手机客户端与我们烧录示例的 ESP32-C3 开发板连接后的截图，配合本文的上面一些说明，可以让我们更直观的理解上面提到的概念。

# 结语

在写本文前，博主自己确实对蓝牙的这些概念不太理解，当初看这些概念的时候也参考了很多很多文章，花了很多时间去记住整理这些概念，到现在使用起来还是需要对着概念图看，尴尬 = =！



**所谓开发蓝牙应用程序，其实就是开发 service 和 characteristic。通过 API，添加自己需要的 characteristic 和 service，**一个蓝牙设备就诞生了。



只要 characteristic 和 service 是符合 GATT 规范的，你可以随意添加任何 characteristic 和 service，并将他们组合成一个专门的蓝牙设备。由于这个蓝牙设备是按照规范来定义的，所以它可以与任何其他蓝牙设备，比如手机，互联互通，并完成所要求的的交互动作。



本文我们基本上把蓝牙 GATT 的概念认识了一遍，就算从来没接触过蓝牙，从本文入手，应该也能算是入门了解过了一些。当然，本文并没有深入的阐述每一个概念，一来对于蓝牙协议，博主也是初学者；二来博主还是以应用为目的，应用就是先能够使用修改起来，再谈深入。



那么蓝牙系列的下一篇文章，我们就要回到示例 GATT server ，分析一下示例程序代码，通过实际的程序加深我们对蓝牙 GATT 的理解，同时开始进行初步的修改测试 。

发布于: 2022-09-29阅读数: 105

版权声明: 本文为 InfoQ 作者【矜辰所致】的原创文章。

原文链接:【https://xie.infoq.cn/article/9c35d44a61bf2f11aa0e5c407】。文章转载请联系作者。

# ESP32-C3 学习测试 蓝牙 篇（四、GATT Server 示例解析）

作者：矜辰所致

- 2022-10-01

  江苏

- 本文字数：13847 字

  阅读完需：约 45 分钟

![ESP32-C3 学习测试 蓝牙 篇（四、GATT Server 示例解析）](https://static001.geekbang.org/infoq/3b/3b7559623426010f8b26f2acf3ca8d59.jpeg)

```
了解了蓝牙 GATT 相关概念，趁热打铁，分析一下官方示例 GATT Server 的应用程序架构。
```

复制代码



# 前言

上一篇文章我们学习了 蓝牙 GATT 相关概念，对于一些基本的专有名词也有了初步的认识，这给我们理解应用程序打下了概念基础 。



本文我们就来分析一下官方示例 GATT Server 的应用程序架构，通过对程序的分析，不仅能更好的理解蓝牙 GATT 的基本概念，还能进一步的明白一些上篇文章不曾深入说明的细节问题。



> ESP32-C3 学习 蓝牙 篇系列博文连接：
>
> 自己画一块 ESP32-C3 的开发板（第一次使用立创 EDA）（PCB 到手）
>
> https://xie.infoq.cn/article/30387388381a0d915b2494f91
>
> 
>
> 开发环境是乐鑫官方的 ESP-IDF， 基于 VScode 插件搭建好的：
>
> ESP32-C3 VScode 开发环境搭建（基于乐鑫官方 ESP-IDF——Windows 和 Ubuntu 双环境）
>
> https://xie.infoq.cn/article/5b639e112cabba00cc1b8941a
>
> 
>
> 蓝牙篇系列相关博文：
>
> ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）
>
> https://xie.infoq.cn/article/efbe5651b35c9d54c69bc0ab2
>
> ESP32-C3 学习测试 蓝牙 篇（二、蓝牙调试 APP、开发板手机连接初体验）
>
> https://xie.infoq.cn/article/a422913b3b0420b1ae7c1436d
>
> ESP32-C3 学习测试 蓝牙 篇（三、认识蓝牙 GATT 协议）
>
> https://xie.infoq.cn/article/9c35d44a61bf2f11aa0e5c407

# 一、GATT Server 示例分析

作为一个单独的应用程序，GATT Server 代码量也算是多的了，我们根据应用程序运行流程从 app_main 开始。

## 1.1 初始化

1、NVS 初始化，在使用 wifi 的时候我们也需要初始化 NVS（Non-volatile repository:非易失存储库，ESP32中的此段分区可以加密），用来存储一些比较信息：



```c
ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
```

复制代码



2、释放一下 `ESP_BT_MODE_CLASSIC_BT`，就是释放经典蓝牙资源，保证设备不工作在经典蓝牙下面：



```c
ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
```

复制代码



3、按照默认配置`BT_CONTROLLER_INIT_CONFIG_DEFAULT`，初始化 蓝牙控制器：



```c
esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
//初始化蓝牙控制器，此函数只能被调用一次，且必须在其他蓝牙功能被调用之前调用
ret = esp_bt_controller_init(&bt_cfg);
if (ret) {
    ESP_LOGE(GATTS_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
    return;
}
```

复制代码



4、使能蓝牙控制器，工作在 BLE mode:



```c
//如果想要动态改变蓝牙模式不能直接调用该函数，先disable关闭蓝牙再使用该API来改变蓝牙模式
ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
if (ret) {
    ESP_LOGE(GATTS_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
    return;
}
```

复制代码



5、初始化蓝牙主机，使能蓝牙主机：



```c
//蓝牙栈 `bluedroid stack` 包括了BT和 BLE 使用的基本的define和API
ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s init bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }
```

复制代码



6、注册 GATT 回调函数，回调函数具体内容会在下文说明：



```c
ret = esp_ble_gatts_register_callback(gatts_event_handler);
if (ret){
ESP_LOGE(GATTS_TAG, "gatts register error, error code = %x", ret);
    return;
}
```

复制代码



7、注册 GAP 回调函数，在前面的文章我们说过：蓝牙是通过 GAP 建立通信的，所以在这个回调函数中定义了在广播期间蓝牙设备的一些操作：



```c
ret = esp_ble_gap_register_callback(gap_event_handler);
if (ret){
    ESP_LOGE(GATTS_TAG, "gap register error, error code = %x", ret);
    return;
}
```

复制代码



8、 注册 service ：



```c
/*
当调用esp_ble_gatts_app_register()注册一个应用程序Profile(Application Profile)，
将触发ESP_GATTS_REG_EVT事件，
除了可以完成对应profile的gatts_if的注册,
还可以调用esp_bel_create_attr_tab()来创建profile Attributes 表
或创建一个服务esp_ble_gatts_create_service()                         
*/
ret = esp_ble_gatts_app_register(PROFILE_A_APP_ID);
if (ret){
    ESP_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
    return;
}
ret = esp_ble_gatts_app_register(PROFILE_B_APP_ID);
if (ret){
    ESP_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
    return;
}
```

复制代码



9、设置 mtu ，mtu 相关说明如下：



```
MTU: MAXIMUM TRANSMISSION UNIT
最大传输单元，
指在一个PDU 能够传输的最大数据量(多少字节可以一次性传输到对方)。
 
PDU：Protocol Data Unit 
协议数据单元,
在一个传输单元中的有效传输数据。
```

复制代码



```c
esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
if (local_mtu_ret){
    ESP_LOGE(GATTS_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
}
```

复制代码

## 1.2 回调函数

在示例中有好几个回调函数，我们依次来看：

### gatts_event_handler

先来看第一个回调函数`gatts_event_handler`：



```c
/*
参数说明：
event: 
esp_gatts_cb_event_t 枚举类型，表示调用该回调函数时的事件(或蓝牙的状态)

gatts_if: 
esp_gatt_if_t (uint8_t) 这是GATT访问接口类型，
通常在GATT客户端上不同的应用程序用不同的gatt_if(不同的Application profile对应不同的gatts_if) ，
调用esp_ble_gatts_app_register()时，
注册Application profile 就会有一个gatts_if。

param: esp_ble_gatts_cb_param_t 指向回调函数的参数，是个联合体类型，
不同的事件类型采用联合体内不同的成员结构体。
*/
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    /* 
    If event is register event, store the gatts_if for each profile 
    判断是否是 GATT 的注册事件
    */
    if (event == ESP_GATTS_REG_EVT) {
         /* 
         确定底层GATT运行成功
         触发ESP_GATTS_REG_EVT时，完成对每个profile 的gatts_if 的注册
         */
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gatts_if = gatts_if;
        } else {
            ESP_LOGI(GATTS_TAG, "Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }
    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback 
     * 如果gatts_if == 某个Profile的gatts_if时，调用对应profile的回调函数处理事情。
     */
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            if (gatts_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gatts_if == gl_profile_tab[idx].gatts_if) {
                if (gl_profile_tab[idx].gatts_cb) {
                    gl_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}
</code></font>


 这个函数的主要作用：导入 GATT 的 profiles。



这个函数注册完成之后，就会在 ble 协议任务函数中运行，将程序前面定义的 profiles 导入：
 
在这两个 profiles 中，每一个都有自己对于的回调函数：gatts_profile_a_event_handler 和 gatts_profile_b_event_handler， 这也是我们本示例的关键函数，下面我们会来分析。



.

gap_event_handler
第二个，GAP 事件回调函数gap_event_handler，



我们在上一篇文章分析过，GAP 定义了在广播期间蓝牙设备的一些操作，蓝牙是通过 GAP 建立通信的（说明看代码注释，了解 GAP 各个事件的含义）：



<font color="#0033FF"><font color="#0033FF"><code class="language-c">/*
其中开始广播 adv_params 的参数定义为：
static esp_ble_adv_params_t adv_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};
*/
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
#ifdef CONFIG_SET_RAW_ADV_DATA
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done==0){
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done==0){
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
#else
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT: //广播数据设置完成事件标志
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);//开始广播
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT://广播扫描相应设置完成标志
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
#endif
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: //开始广播事件标志
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TAG, "Advertising start failed\n");
        }
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT: //停止广播事件标志
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TAG, "Advertising stop failed\n");
        } else {
            ESP_LOGI(GATTS_TAG, "Stop adv successfully\n");
        }
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT: // 设备连接事件,可获取当前连接的设备信息
         ESP_LOGI(GATTS_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    default:
        break;
    }
}
```

复制代码



 这个函数的主要作用：导入 GATT 的 profiles。



这个函数注册完成之后，就会在 ble 协议任务函数中运行，将程序前面定义的 profiles 导入：

![img](https://img-blog.csdnimg.cn/b467f0d40a8e40769a5cecb08687f991.png) 

在这两个 profiles 中，每一个都有自己对于的回调函数：`gatts_profile_a_event_handler` 和 `gatts_profile_b_event_handler`， 这也是我们本示例的关键函数，下面我们会来分析。





.

### gap_event_handler

第二个，GAP 事件回调函数`gap_event_handler`，



我们在上一篇文章分析过，GAP 定义了在广播期间蓝牙设备的一些操作，蓝牙是通过 GAP 建立通信的（说明看代码注释，了解 GAP 各个事件的含义）：



```c
switch (event) {
    /*
    展示了一个Service的创建
    GATT注册事件，添加 service的基本信息，设置BLE名称
    */
    case ESP_GATTS_REG_EVT:
        ESP_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
        gl_profile_tab[PROFILE_A_APP_ID].service_id.is_primary = true;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.inst_id = 0x00;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_A;

        esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(TEST_DEVICE_NAME);
        if (set_dev_name_ret){
            ESP_LOGE(GATTS_TAG, "set device name failed, error code = %x", set_dev_name_ret);
        }
#ifdef CONFIG_SET_RAW_ADV_DATA 
        esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
        if (raw_adv_ret){
            ESP_LOGE(GATTS_TAG, "config raw adv data failed, error code = %x ", raw_adv_ret);
        }
        adv_config_done |= adv_config_flag;
        esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
        if (raw_scan_ret){
            ESP_LOGE(GATTS_TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
        }
        adv_config_done |= scan_rsp_config_flag;
#else
        //config adv data
        esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
        if (ret){
            ESP_LOGE(GATTS_TAG, "config adv data failed, error code = %x", ret);
        }
        adv_config_done |= adv_config_flag;
        //config scan response data
        ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
        if (ret){
            ESP_LOGE(GATTS_TAG, "config scan response data failed, error code = %x", ret);
        }
        adv_config_done |= scan_rsp_config_flag;

#endif
        esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_A_APP_ID].service_id, GATTS_NUM_HANDLE_TEST_A);
        break;
    case ESP_GATTS_READ_EVT: { //GATT读取事件，手机读取开发板的数据
        ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
        esp_gatt_rsp_t rsp;
        memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
        rsp.attr_value.handle = param->read.handle;
        rsp.attr_value.len = 4;
        rsp.attr_value.value[0] = 0xde;
        rsp.attr_value.value[1] = 0xed;
        rsp.attr_value.value[2] = 0xbe;
        rsp.attr_value.value[3] = 0xef;
        esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    ESP_GATT_OK, &rsp);
        break;
    }
    case ESP_GATTS_WRITE_EVT: { //GATT写事件，手机给开发板的发送数据，不需要回复
        ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d", param->write.conn_id, param->write.trans_id, param->write.handle);
        if (!param->write.is_prep){
            ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
            esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
            if (gl_profile_tab[PROFILE_A_APP_ID].descr_handle == param->write.handle && param->write.len == 2){
                uint16_t descr_value = param->write.value[1]<<8 | param->write.value[0];
                if (descr_value == 0x0001){
                    if (a_property & ESP_GATT_CHAR_PROP_BIT_NOTIFY){
                        ESP_LOGI(GATTS_TAG, "notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i%0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(notify_data), notify_data, false);
                    }
                }else if (descr_value == 0x0002){
                    if (a_property & ESP_GATT_CHAR_PROP_BIT_INDICATE){
                        ESP_LOGI(GATTS_TAG, "indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i%0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(indicate_data), indicate_data, true);
                    }
                }
                else if (descr_value == 0x0000){
                    ESP_LOGI(GATTS_TAG, "notify/indicate disable ");
                }else{
                    ESP_LOGE(GATTS_TAG, "unknown descr value");
                    esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
                }

            }
        }
        example_write_event_env(gatts_if, &a_prepare_write_env, param);
        break;
    }
    case ESP_GATTS_EXEC_WRITE_EVT: //GATT写事件，手机给开发板的发送数据，需要回复
        ESP_LOGI(GATTS_TAG,"ESP_GATTS_EXEC_WRITE_EVT");
        esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
        example_exec_write_event_env(&a_prepare_write_env, param);
        break;
    case ESP_GATTS_MTU_EVT:
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
        break;
    case ESP_GATTS_UNREG_EVT:
        break;
    //创建 GATT事件,基本参数的设置，将Characteristic加到service中，完成触发下面事件
    case ESP_GATTS_CREATE_EVT: 
        ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].service_handle = param->create.service_handle;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_TEST_A;

        esp_ble_gatts_start_service(gl_profile_tab[PROFILE_A_APP_ID].service_handle);
        a_property = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
        esp_err_t add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].char_uuid,
                                                        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                                        a_property,
                                                        &gatts_demo_char1_val, NULL);
        if (add_char_ret){
            ESP_LOGE(GATTS_TAG, "add char failed, error code =%x",add_char_ret);
        }
        break;
    case ESP_GATTS_ADD_INCL_SRVC_EVT:
        break;
    //添加Characteristic事件，添加Characteristic的Descriptor，完成触发下面事件
    case ESP_GATTS_ADD_CHAR_EVT: { 
        uint16_t length = 0;
        const uint8_t *prf_char;

        ESP_LOGI(GATTS_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].char_handle = param->add_char.attr_handle;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.uuid.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
        esp_err_t get_attr_ret = esp_ble_gatts_get_attr_value(param->add_char.attr_handle,  &length, &prf_char);
        if (get_attr_ret == ESP_FAIL){
            ESP_LOGE(GATTS_TAG, "ILLEGAL HANDLE");
        }

        ESP_LOGI(GATTS_TAG, "the gatts demo char length = %x\n", length);
        for(int i = 0; i < length; i++){
            ESP_LOGI(GATTS_TAG, "prf_char[%x] =%x\n",i,prf_char[i]);
        }
        esp_err_t add_descr_ret = esp_ble_gatts_add_char_descr(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].descr_uuid,
                                                                ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, NULL, NULL);
        if (add_descr_ret){
            ESP_LOGE(GATTS_TAG, "add char descr failed, error code =%x", add_descr_ret);
        }
        break;
    }
    case ESP_GATTS_ADD_CHAR_DESCR_EVT:// 添加描述事件
        gl_profile_tab[PROFILE_A_APP_ID].descr_handle = param->add_char_descr.attr_handle;
        ESP_LOGI(GATTS_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                 param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
        break;
    case ESP_GATTS_DELETE_EVT:
        break;
    case ESP_GATTS_START_EVT:
        ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n",
                 param->start.status, param->start.service_handle);
        break;
    case ESP_GATTS_STOP_EVT:
        break;
    case ESP_GATTS_CONNECT_EVT: { // GATT 连接事件
        esp_ble_conn_update_params_t conn_params = {0};
        memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
        /* For the IOS system, please reference the apple official documents about the ble connection parameters restrictions. */
        conn_params.latency = 0;
        conn_params.max_int = 0x20;    // max_int = 0x20*1.25ms = 40ms
        conn_params.min_int = 0x10;    // min_int = 0x10*1.25ms = 20ms
        conn_params.timeout = 400;    // timeout = 400*10ms = 4000ms
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:",
                 param->connect.conn_id,
                 param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                 param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
        gl_profile_tab[PROFILE_A_APP_ID].conn_id = param->connect.conn_id;
        //start sent the update connection parameters to the peer device.
        esp_ble_gap_update_conn_params(&conn_params);
        break;
    }
    case ESP_GATTS_DISCONNECT_EVT://断开连接事件
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
        esp_ble_gap_start_advertising(&adv_params);
        break;
    case ESP_GATTS_CONF_EVT: //GATT配置事件
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT, status %d attr_handle %d", param->conf.status, param->conf.handle);
        if (param->conf.status != ESP_GATT_OK){
            esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
        }
        break;
    case ESP_GATTS_OPEN_EVT:
    case ESP_GATTS_CANCEL_OPEN_EVT:
    case ESP_GATTS_CLOSE_EVT:
    case ESP_GATTS_LISTEN_EVT:
    case ESP_GATTS_CONGEST_EVT:
    default:
        break;
    }
}
```

复制代码



说明：GAP 的回调函数有很多，通过枚举`esp_gap_ble_cb_event_t`可查看。这里我们只说明上面回调函数使用到的。



.

### ☆ gatts_profile_b_event_handler ☆

本示例的核心部分， GATT 回调函数`gatts_profile_a_event_handler`，



理解了他将让自己在以后蓝牙 GATT 的开发中更加得心应手（说明看代码注释，了解 GATT 各个事件的含义）：



```c
switch (event) {
    /*
    展示了一个Service的创建
    GATT注册事件，添加 service的基本信息，设置BLE名称
    */
    case ESP_GATTS_REG_EVT:
        ESP_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
        gl_profile_tab[PROFILE_A_APP_ID].service_id.is_primary = true;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.inst_id = 0x00;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_A;

        esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(TEST_DEVICE_NAME);
        if (set_dev_name_ret){
            ESP_LOGE(GATTS_TAG, "set device name failed, error code = %x", set_dev_name_ret);
        }
#ifdef CONFIG_SET_RAW_ADV_DATA 
        esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
        if (raw_adv_ret){
            ESP_LOGE(GATTS_TAG, "config raw adv data failed, error code = %x ", raw_adv_ret);
        }
        adv_config_done |= adv_config_flag;
        esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
        if (raw_scan_ret){
            ESP_LOGE(GATTS_TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
        }
        adv_config_done |= scan_rsp_config_flag;
#else
        //config adv data
        esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
        if (ret){
            ESP_LOGE(GATTS_TAG, "config adv data failed, error code = %x", ret);
        }
        adv_config_done |= adv_config_flag;
        //config scan response data
        ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
        if (ret){
            ESP_LOGE(GATTS_TAG, "config scan response data failed, error code = %x", ret);
        }
        adv_config_done |= scan_rsp_config_flag;

#endif
        esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_A_APP_ID].service_id, GATTS_NUM_HANDLE_TEST_A);
        break;
    case ESP_GATTS_READ_EVT: { //GATT读取事件，手机读取开发板的数据
        ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
        esp_gatt_rsp_t rsp;
        memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
        rsp.attr_value.handle = param->read.handle;
        rsp.attr_value.len = 4;
        rsp.attr_value.value[0] = 0xde;
        rsp.attr_value.value[1] = 0xed;
        rsp.attr_value.value[2] = 0xbe;
        rsp.attr_value.value[3] = 0xef;
        esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    ESP_GATT_OK, &rsp);
        break;
    }
    case ESP_GATTS_WRITE_EVT: { //GATT写事件，手机给开发板的发送数据，不需要回复
        ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d", param->write.conn_id, param->write.trans_id, param->write.handle);
        if (!param->write.is_prep){
            ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
            esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
            if (gl_profile_tab[PROFILE_A_APP_ID].descr_handle == param->write.handle && param->write.len == 2){
                uint16_t descr_value = param->write.value[1]<<8 | param->write.value[0];
                if (descr_value == 0x0001){
                    if (a_property & ESP_GATT_CHAR_PROP_BIT_NOTIFY){
                        ESP_LOGI(GATTS_TAG, "notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i%0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(notify_data), notify_data, false);
                    }
                }else if (descr_value == 0x0002){
                    if (a_property & ESP_GATT_CHAR_PROP_BIT_INDICATE){
                        ESP_LOGI(GATTS_TAG, "indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i%0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(indicate_data), indicate_data, true);
                    }
                }
                else if (descr_value == 0x0000){
                    ESP_LOGI(GATTS_TAG, "notify/indicate disable ");
                }else{
                    ESP_LOGE(GATTS_TAG, "unknown descr value");
                    esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
                }

            }
        }
        example_write_event_env(gatts_if, &a_prepare_write_env, param);
        break;
    }
    case ESP_GATTS_EXEC_WRITE_EVT: //GATT写事件，手机给开发板的发送数据，需要回复
        ESP_LOGI(GATTS_TAG,"ESP_GATTS_EXEC_WRITE_EVT");
        esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
        example_exec_write_event_env(&a_prepare_write_env, param);
        break;
    case ESP_GATTS_MTU_EVT:
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
        break;
    case ESP_GATTS_UNREG_EVT:
        break;
    //创建 GATT事件,基本参数的设置，将Characteristic加到service中，完成触发下面事件
    case ESP_GATTS_CREATE_EVT: 
        ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].service_handle = param->create.service_handle;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_TEST_A;

        esp_ble_gatts_start_service(gl_profile_tab[PROFILE_A_APP_ID].service_handle);
        a_property = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
        esp_err_t add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].char_uuid,
                                                        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                                        a_property,
                                                        &gatts_demo_char1_val, NULL);
        if (add_char_ret){
            ESP_LOGE(GATTS_TAG, "add char failed, error code =%x",add_char_ret);
        }
        break;
    case ESP_GATTS_ADD_INCL_SRVC_EVT:
        break;
    //添加Characteristic事件，添加Characteristic的Descriptor，完成触发下面事件
    case ESP_GATTS_ADD_CHAR_EVT: { 
        uint16_t length = 0;
        const uint8_t *prf_char;

        ESP_LOGI(GATTS_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].char_handle = param->add_char.attr_handle;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.uuid.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
        esp_err_t get_attr_ret = esp_ble_gatts_get_attr_value(param->add_char.attr_handle,  &length, &prf_char);
        if (get_attr_ret == ESP_FAIL){
            ESP_LOGE(GATTS_TAG, "ILLEGAL HANDLE");
        }

        ESP_LOGI(GATTS_TAG, "the gatts demo char length = %x\n", length);
        for(int i = 0; i < length; i++){
            ESP_LOGI(GATTS_TAG, "prf_char[%x] =%x\n",i,prf_char[i]);
        }
        esp_err_t add_descr_ret = esp_ble_gatts_add_char_descr(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].descr_uuid,
                                                                ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, NULL, NULL);
        if (add_descr_ret){
            ESP_LOGE(GATTS_TAG, "add char descr failed, error code =%x", add_descr_ret);
        }
        break;
    }
    case ESP_GATTS_ADD_CHAR_DESCR_EVT:// 添加描述事件
        gl_profile_tab[PROFILE_A_APP_ID].descr_handle = param->add_char_descr.attr_handle;
        ESP_LOGI(GATTS_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                 param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
        break;
    case ESP_GATTS_DELETE_EVT:
        break;
    case ESP_GATTS_START_EVT:
        ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n",
                 param->start.status, param->start.service_handle);
        break;
    case ESP_GATTS_STOP_EVT:
        break;
    case ESP_GATTS_CONNECT_EVT: { // GATT 连接事件
        esp_ble_conn_update_params_t conn_params = {0};
        memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
        /* For the IOS system, please reference the apple official documents about the ble connection parameters restrictions. */
        conn_params.latency = 0;
        conn_params.max_int = 0x20;    // max_int = 0x20*1.25ms = 40ms
        conn_params.min_int = 0x10;    // min_int = 0x10*1.25ms = 20ms
        conn_params.timeout = 400;    // timeout = 400*10ms = 4000ms
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:",
                 param->connect.conn_id,
                 param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                 param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
        gl_profile_tab[PROFILE_A_APP_ID].conn_id = param->connect.conn_id;
        //start sent the update connection parameters to the peer device.
        esp_ble_gap_update_conn_params(&conn_params);
        break;
    }
    case ESP_GATTS_DISCONNECT_EVT://断开连接事件
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
        esp_ble_gap_start_advertising(&adv_params);
        break;
    case ESP_GATTS_CONF_EVT: //GATT配置事件
        ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT, status %d attr_handle %d", param->conf.status, param->conf.handle);
        if (param->conf.status != ESP_GATT_OK){
            esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
        }
        break;
    case ESP_GATTS_OPEN_EVT:
    case ESP_GATTS_CANCEL_OPEN_EVT:
    case ESP_GATTS_CLOSE_EVT:
    case ESP_GATTS_LISTEN_EVT:
    case ESP_GATTS_CONGEST_EVT:
    default:
        break;
    }
}
```

复制代码



除了上面代码中事件的简单注释，还有一些需要说明的地方：



1、 在`ESP_GATTS_CREATE_EVT`事件中调用了函数：



```c
esp_err_t esp_ble_gatts_start_service(uint16_t service_handle)
```

复制代码



该函数的作用是启动 GATT 服务。



再然后调用函数：



```c
esp_err_t esp_ble_gatts_add_char(uint16_t service_handle, 
                                 esp_bt_uuid_t  *char_uuid,
                                 esp_gatt_perm_t perm, 
                                 esp_gatt_char_prop_t property, esp_attr_value_t *char_val,
                                 esp_attr_control_t *control)
```

复制代码



来添加特性(特征的 UUID， 特征值描述符属性权限， 特征属性、特征值、属性响应控制字节)。



上面的一系列操作会触发`ESP_GATTS_START_EVT`和`ESP_GATTS_ADD_CHAR_EVT`事件



2、上面事件中有 2 个写事件： `ESP_GATTS_WRITE_EVT` 和 `ESP_GATTS_EXEC_WRITE_EVT`其中`ESP_GATTS_EXEC_WRITE_EVT` 事件在接收到写数据之后需要为 Client 回复数据 ，前者不需要。



.

### GATT 事件流程

在没有连接之前：注册->创建->启动->添加特征->添加特征描述：



```
ESP_GATTS_REG_EVT`—>`ESP_GATTS_CREATE_EVT`—>`ESP_GATTS_START_EVT`—>`ESP_GATTS_ADD_CHAR_EVT`—>`ESP_GATTS_ADD_CHAR_DESCR_EVT
```



流程说明：



在 Demo 的`ESP_GATTS_REG_EVT`事件中，调用`esp_ble_gap_set_device_name(char *)`来设置蓝牙设备名字；调用`esp_ble_gap_config_adv_data()`来配置广播数据；



最后调用`esp_ble_gatts_create_service()`指定 gatts_if 和 service_id 来创建服务<实际调用 `btc_transfer_context()` 来完成服务的创建和调用回调函数>。



服务创建完成就会触发回调函数向 profile 报告状态和服务 ID。Service_id 对于后面添加 included serivces 和 characteristics 和 descriptor 都要用到。触发`ESP_GATTS_CREATE_EVT`事件



在 Demo 的`ESP_GATTS_CREATE_EVT`中调用`esp_ble_gatts_start_service(uint16_t service_handle)`来启动服务；



再调用 `esp_ble_gatts_add_char()` 来添加特性(特征的 UUID， 特征值描述符属性权限， 特征属性、特征值、属性响应控制字节)。



触发`ESP_GATTS_START_EVT`和`ESP_GATTS_ADD_CHAR_EVT`事件，在`ESP_GATTS_ADD_CHAR_EVT`事件中，获取特征值调用`esp_err_tesp_ble_gatts_add_char_descr()`来添加特征描述符。



在连接之后：



```
CONNECT_EVT`—>`ESP_GATTS_MTU_EVT`—>`GATT_WRITE_EVT`—>`ESP_GATTS_CONF_EVT`—>`GATT_READ_EVT
```



参考博文：[从ESP32 BLE应用理解GATT](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fzhejfl%2Farticle%2Fdetails%2F85136102%3Fops_request_misc%3D%257B%2522request%255Fid%2522%253A%2522165362069716781667815116%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D%26request_id%3D165362069716781667815116%26biz_id%3D0%26utm_medium%3Ddistribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-4-85136102-null-null.142%5Ev11%5Epc_search_result_control_group%2C157%5Ev12%5Econtrol%26utm_term%3D%E4%BE%8B%E7%A8%8Bgatt_server%20%E8%AE%B2%E8%A7%A3%26spm%3D1018.2226.3001.4187)



[ESP32学习笔记（7）蓝牙GATT服务应用](https://xie.infoq.cn/link?target=https%3A%2F%2Fblog.csdn.net%2Fweixin_41034400%2Farticle%2Fdetails%2F115189286)

### esp_ble_gatts_create_service

在提一个函数，在上面介绍的回调函数时间中说到 `ESP_GATTS_REG_EVT` 最后回调用 `esp_ble_gatts_create_service` 来创建服务：



创建一个 service。当一个 service 创建成功后，`ESP_CREATE_SERVICE_EVT`事件触发回调函数被调用，该回调函数报告了 profile 的 stauts 和 service ID。当要添加 include service 和 characteristics//descriptors 入服务 service，Service ID 在回调函数中用到。



```c
/*
gatts_if：GATT 服务器访问接口

service_id: 服务UUID相关信息

num_handle:
该服务所需的句柄数 service、characteristic declaration、 characteristic value、characteristic description 的句柄数总和。
Demo中用的是4（1+3），如果有两个特征，则为7（1+3+3）.
*/
esp_err_t esp_ble_gatts_create_service(esp_gatt_if_t gatts_if,
                                       esp_gatt_srvc_id_t *service_id, uint16_t num_handle)
{
    btc_msg_t msg;
    btc_ble_gatts_args_t arg;

    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTS;
    msg.act = BTC_GATTS_ACT_CREATE_SERVICE;
    arg.create_srvc.gatts_if = gatts_if;
    arg.create_srvc.num_handle = num_handle;
    memcpy(&arg.create_srvc.service_id, service_id, sizeof(esp_gatt_srvc_id_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gatts_args_t), NULL) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}
```

复制代码

# 二、示例测试

根据上面的代码分析和上一篇文章的内容，我们可以尝试一下对示例进行一定的测试修改。



当然目前来说，还是怎么简单怎么来。

## 2.1 Service 和 UUID

Service 个数，我们示例中是使用了注册了 2 个 Service ，首先说明一下上一篇文章中，我们说到示例连接后能够获取到的 Service 为 4 个，实际上前面 2 个是固有的，后面 2 个才是我们程序中注册的：

![img](https://img-blog.csdnimg.cn/2f0ec47abaeb4699a646744b7caee661.png) 







我们通过程序中定义的 UUID 也能够看出来：

![img](https://img-blog.csdnimg.cn/8c1f9f9f581743ce91adbaeb23a2c3db.png) 







在程序中其设置的位置如下：

![img](https://img-blog.csdnimg.cn/e60b68530dab4758b412cc6c60ab9de0.png) 







正好讲到 UUID ，可以发现 characteristic 的 UUID 也和定义的一样：

![img](https://img-blog.csdnimg.cn/1079f8feeb0a4097995c76aaf67bcfb5.png) 







在程序中其设置的位置如下：

![img](https://img-blog.csdnimg.cn/a94f4b8f4be747c7a363684987cbb4e3.png) 





## 2.2 characteristic

characteristic 的创建位置在程序中对应的位置如下：

![img](https://img-blog.csdnimg.cn/c5457252baec4ed087c4938c0ddc8ee8.png) 

更多的一些说明需要等熟悉了以后再来更新。



## 2.3 数据收发

我们的蓝牙应用的最终目的还是数据的交互，数据收发，我们前面说了好几篇文章都没有切实的体会到数据的收发，现在终于要开始测试了。



与蓝牙设备的数据交互，可以认为就是对 Characteristci 进行读写即可达到与其通信的目的。



示例中在使用 `esp_ble_gatts_add_char` 函数添加 Characteristci 时就定义了可读可写属性：

![img](https://img-blog.csdnimg.cn/b0403524efb5477f846096ade7319fba.png) 







我们下面就来通过手机与开发板进行数据的读写测试:



**读数据：**



我们通过手机端进行如下操作：



上图中，我们读取到了来自 Server 的数据，在程序中对应的实现部分为：



<3 所以可以想象，如果我们把传感器的数据放在这些 value 中，那么设备读取数据，是不是就可以读取到传感器的数据了。



另外说明：在 Client 端有一个按钮：接收通知数据，对其进行操作有如下 LOG：



这里的原因暂时不理解，等后期明白了会更新说明。



**写数据：**



除了读数据，我们通过手机端也可以对设备进行写数据（当然前提是这个 characteristic 添加的时候支持写）：



对于写数据，在程序中对应的实现部分为：



和发送类似，这里我们可以添加一些相关的代码，收到 Client 发送的特定指令，进行特定的操作，简单的比如切换 LED，采集一次数据等。

# 结语

本文经过对示例程序的分析说明，然后通过对比手机端读取到的信息，进行了简单的数据读写测试，了解了程序的设计框架，也算是入门了 ESP-IDF 的蓝牙 GATT 开发。



当然我们还只停留在理论分析阶段，实际上到现在我们都不曾真正的动手修改添加过程序代码。对于我计划的以应用为目的来说，至少也需要使用蓝牙 BLE 通过手机能够接收到开发板上各种传感器的数据，然后通过手机可以对开发板进行一些控制操作。



接下来的文章我们的学习测试就会一步一步的朝着这个最终的目的而进行，加油↖(^ω^)↗！



发布于: 2022-10-01阅读数: 34

版权声明: 本文为 InfoQ 作者【矜辰所致】的原创文章。

原文链接:【https://xie.infoq.cn/article/743c10571e00b2e895cecb5d1】。文章转载请联系作者。

# ESP32-C3 学习测试 蓝牙 篇（五、添加 characteristic）

作者：矜辰所致

- 2022-10-02

  江苏

- 本文字数：3412 字

  阅读完需：约 11 分钟

![ESP32-C3 学习测试 蓝牙 篇（五、添加 characteristic）](https://static001.geekbang.org/infoq/3b/3b7559623426010f8b26f2acf3ca8d59.jpeg)

```
前面的蓝牙部分都是基础说明，示例分析，本文就来改他一改
```

复制代码



# 前言

又隔了一段时间没接着玩 ESP32-C3 ，又把自己的蓝牙文章重新看了一遍才可以继续进行……



嗯…… 看完忽然想了好多问题，尤其是针对上一篇文章的示例，在想到蓝牙初始化，通讯的时候，那些流程细节，虽然知道基本的步骤，但是每一个本质上是进行了哪些细节操作还是完全没头绪啊，有时候使用这种完全不知道本质的代码，感觉心慌慌，嗯……



算了，先不烦这些，认清目标：



我们不是来研究蓝牙协议的，我们是来使用 ESP32-C3 跑蓝牙协议，用来 数据传输通讯的。我们要会用 ESP—IDF 提供的示例框架，根据自己的实际需求修改代码，这就是我们最终的目的 ！(熟悉蓝牙协议栈的朋友就随意了 (灬ꈍ ꈍ灬))



最终我们要实现一个小示例，通过蓝牙通讯，把传感器的数据发送给手机，然后手机也可以控制开发板上的 LED 灯。



我们在上文说过蓝牙应用程序开发，就是开发 service 和 characteristic。通过 API，添加自己需要的 characteristic 和 service。



所以今天，我们势必得在示例基础上动一动，就先在现有 Service 的基础上，添加一个额外的 characteristic。



> ESP32-C3 学习 蓝牙 篇系列博文连接：
>
> 自己画一块 ESP32-C3 的开发板（第一次使用立创 EDA）（PCB 到手）
>
> https://xie.infoq.cn/article/30387388381a0d915b2494f91
>
> 
>
> 开发环境是乐鑫官方的 ESP-IDF， 基于 VScode 插件搭建好的：
>
> ESP32-C3 VScode 开发环境搭建（基于乐鑫官方 ESP-IDF——Windows 和 Ubuntu 双环境）
>
> https://xie.infoq.cn/article/5b639e112cabba00cc1b8941a
>
> 
>
> 蓝牙篇系列相关博文：
>
> ESP32-C3 学习测试 蓝牙 篇（一、认识 ESP-IDF 的蓝牙框架、简单的了解蓝牙协议栈）
>
> https://xie.infoq.cn/article/efbe5651b35c9d54c69bc0ab2
>
> ESP32-C3 学习测试 蓝牙 篇（二、蓝牙调试 APP、开发板手机连接初体验）
>
> https://xie.infoq.cn/article/a422913b3b0420b1ae7c1436d
>
> ESP32-C3 学习测试 蓝牙 篇（三、认识蓝牙 GATT 协议）
>
> https://xie.infoq.cn/article/9c35d44a61bf2f11aa0e5c407
>
> ESP32-C3 学习测试 蓝牙 篇（四、GATT Server 示例解析）
>
> https://xie.infoq.cn/article/743c10571e00b2e895cecb5d1



# 一、示例更换说明

在我们前面几篇文章，都是从 GATT Server 示例说起的，本来也是计划从 GATT Server 示例来做以后测试的修改框架。



但是自己想增加一个 characteristic 的时候，发现无从下手。正好在上一篇文章《ESP32-C3 学习测试 蓝牙 篇（四、GATT Server 示例解析）》后又小伙伴留言问过，官方是不是推推荐 gatt_server_service_table ？

## gatt_server_service_table

所以还是回头看了自己蓝牙篇的第一篇文章，看了下这两个的比较（当时属于概括，也没有什么特别说明）：



![img](https://static001.geekbang.org/infoq/11/114762af9f0537bbe539ec9ce5c3e1d9.png)



于是乎还是得找到官方自己的示例说明，仔细看了一下示例说明，官方对 GATT Server  示例其实有说明，推荐了 gatt_server_service_table 示例，如下图：



![img](https://static001.geekbang.org/infoq/f9/f9e422612c01cc2e0e1dd64d7997b497.png)



在乐鑫官方论坛我也找到过类似的问题，其中有说明 GATT Server 是一种根据事件串行创建服务、特征值和描述符的，创建多服务或者特征值时不太方便，如下图：



![img](https://static001.geekbang.org/infoq/27/27263d00e37cc5f3cf43f0c7f84aaa12.png)



.



所以我们需要使用示例 gatt_server_service_table 作为我们的测试修改的示例，我们正常的新建一个示例，先简单看看示例框架：



```
/*  gatt_server_service_table  示例初始化  gatts_table_creat_demo.c*/void app_main(void){    esp_err_t ret;    /* Initialize NVS. */    ret = nvs_flash_init();    ESP_ERROR_CHECK( ret );    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);    ret = esp_bluedroid_init();    ret = esp_bluedroid_enable();    ret = esp_ble_gatts_register_callback(gatts_event_handler);    ret = esp_ble_gap_register_callback(gap_event_handler);    ret = esp_ble_gatts_app_register(ESP_APP_ID);    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);    }}
```

复制代码



初始化流程是和上一篇文章分析的 GATT Server  示例是一样的， 所以这里我们就不再次分析了。



在 ESP-IDF 中 GATT Server 的示例中，官方提供了一个 方便添加修改特征值和服务的示例 gatt_server_service_table 以供开发者使用。



# 二、示例测试

新的例程，不管三七二十一，先跑起来看看，程序正常便宜烧录，然后通过手机蓝牙助手可以看到设备：



![img](https://static001.geekbang.org/infoq/84/8434e85e025850ab6bde96d251f1d36d.png)



我们前面已经有几篇文章的基础，所以本文不用讲太多理论，我们直接用图文说明几个地方。

## 2.1 广播包

Server 设备还没有连接的时候，会一直发送广播包，我们在手机端可以点击设备查看广播包等信息。



在 gatt_server_service_table 示例程序中广播包的定义用数组`raw_adv_data`表示，如下图：



![img](https://static001.geekbang.org/infoq/f5/f5caf4820fd38fc06c6acaa2334412b9.png)



这里在额外放一下 GATT Server 示例 的广播包，除了前面 3 个字节，后面都对不上，这里暂时我也不明白 = =！



![img](https://static001.geekbang.org/infoq/46/46309f333b3418577714d0caadf32115.png)

### 2.1.1 设备名称

对于我们上一篇文章说明的 GATT Server 示例 ，我们直接修改宏定义就可以改变设备名称：



![img](https://static001.geekbang.org/infoq/02/02a6b3c1f17b6ef611c3c7b1b87a0bef.png)



但是对于本文 gatt_server_service_table 示例来说，修改宏定义并不能改变设备名称：



![img](https://static001.geekbang.org/infoq/43/43d8b43d67cb87f5a97a00596eff38c5.png)



说明： 这里我们是看表象，或许本质上，只是个关联设置问题，但是我们现在目的是快速使用，里面的本质这些我们暂时不考虑。



在广播包中会包含一些设置好的信息，其中就有设备名称，在我们的 gatt_server_service_table 示例中，可以看到广播包中有关于设备名称的部分：



![img](https://static001.geekbang.org/infoq/ac/ac6704433b46b6fc736ee206b0483a18.png)



所以，如果我们需要修改设备名称，我们直接在这个数组里面修改，但是不要忘了长度，修改示例如下：



![img](https://static001.geekbang.org/infoq/14/14a946abedbb55663a9be92811b4c47c.png)

## 2.2 服务与特征值

我们点击连接设备，可以看到 gatt_server_service_table 示例中的 Service 与 characteristic ，如下图：



![img](https://static001.geekbang.org/infoq/2e/2e01ab1125734ad1658721219876734b.png)



对于这些不同的 characteristic ，我结合程序做了个示意图说明：



![img](https://static001.geekbang.org/infoq/10/10ba7f2ed4c2c9f9b8702188faa67384.png)



.

## 2.3 读写操作

读写操作在上一篇文章中，我们已经测试过了，换了一个示例，其实读写的简单测试还是一样的，这里针对几个地方再分别介绍一下。

### 2.3.1 通知 notify

通知，也算是一种可传递的消息，在我们介绍 GATT 协议的时候讲过，如果 characteristic 具有 notify 或 indicate 操作功能时，必须为其添加响应的 CCCD（characteristic descriptor），这一点在程序中创建 characteristic 的时候就有体现：



![img](https://static001.geekbang.org/infoq/6c/6cbfa797c8288b17431425d75b6efb21.png)



对于通知的发送，是通过`esp_ble_gatts_send_indicate` 函数发送，如下图：



![img](https://static001.geekbang.org/infoq/94/949af696d73706ca638f122082df2d13.png)



我们可以修改一下通知的值，测试一下看看：



![img](https://static001.geekbang.org/infoq/f6/f6938d6e5b5964120ff30ebd3b8fc63f.png)



接收不全？ 看了下输出日志，应该是太长了，提示最大应该是 20 字节：



![img](https://static001.geekbang.org/infoq/bf/bf88d6f9400eef3c44207fd1820ab53e.png)



再改一次，这次 OK：



![img](https://static001.geekbang.org/infoq/76/76185cc69b73b479fdd00bceb3c50d26.png)



.



这里还有一个地方需要说明，`esp_ble_gatts_send_indicate` 函数的最后一个参数，当为 false 时候，不需要得到回复，为 true 时，需要得到回复。



![img](https://static001.geekbang.org/infoq/06/0643461e3c26502eab76a7846c7ce0bb.png)

### 2.3.2 值 value

每一个 characteristic 都有自己的 value ，对于示例来，与 characteristic 的 value 关联的地方如下图：



![img](https://static001.geekbang.org/infoq/66/6601e5d9f5712fc0b6983dfcd80cd576.png)



既然知道了位置，那么和通知一样，我们简单修改测试一下：



![img](https://static001.geekbang.org/infoq/82/8244a8d46029cbc0e38d20c0a85ef901.png)



.



这里说明一下，在上面通知部分，我们看到测试示例的日志输出的提示为 attribute value too long，  我们以前说过 characteristic 的条目的实现都是通过 attribute  来表达的，所以对于 notify 的最大长度为 20， 对于  characteristic value 来说也是一样的，最大长度为 20。



上面的示例修改，如果数据长度超过 20 会有问题，手机端读取不到。



这个还有个小疑问， value 的长度大小可不可以自行设定？哪里设定？



这个问题后面如果有需要用到或者学到了再来解答，暂时先提出来。

# 三、示例修改（添加一个 characteristic）

经过上面的基础测试，我们开始在示例结构上添加一个新的 characteristic 。



这里的步骤我就直接使用图文说明，我会把添加的文件名称，代码位置都截图出来：

## 3.1 UUID 定义

![img](https://static001.geekbang.org/infoq/6a/6a39fabb7f549eaa8354f1f2fec7a8c9.png)

## 3.2 枚举 定义

![img](https://static001.geekbang.org/infoq/e1/e178d900ab3654352891df4126606eab.png)

## 3.3 添加属性表

![img](https://static001.geekbang.org/infoq/9d/9d4434c1277d1de6a297cffa33386847.png)



.



完成编译，忽然发现好简单= =！



通过手机查看一下效果：



![img](https://static001.geekbang.org/infoq/ac/ac280df2e3a2e24e0da3023259754f2e.png)



测试过后，读写操作都正常。



最后还是得感叹一下，使用 gatt_server_service_table  添加 characteristic 真的是太方便了。

# 结语

本文我们更换了一下蓝牙 GATT 学习的示例程序，通过进一步的的程序测试，让我们更加的熟悉了 ESP-IDF 提供的示例框架，也知道了如何添加 characteristic。



当然这只算是我们修改的开始，我们接下来要在此基础上学会添加 Service，通过我们自己添加的 Service 和 characteristic 传输我们自己的应用数据。

然后把以前传感器驱动整合进工程，最后实现我们小目标：通过蓝牙通讯，把传感器的数据发送给手机，然后手机也可以控制开发板上的 LED 灯等设备。



路要一步一步走，饭要一口一口吃，本文就到这把，谢谢！

发布于: 2022-10-02阅读数: 47

版权声明: 本文为 InfoQ 作者【矜辰所致】的原创文章。

原文链接:【https://xie.infoq.cn/article/7bb73c3b43f678e773c369d0c】。文章转载请联系作者。

