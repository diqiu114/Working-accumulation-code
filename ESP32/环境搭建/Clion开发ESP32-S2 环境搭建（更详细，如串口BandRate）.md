# Clion开发ESP32-S2 环境搭建

2022-02-12 11:56874阅读 · 17喜欢 · 9评论

[![img](https://i1.hdslb.com/bfs/face/35d4b2fdfc017604b53ab470394eadd396aaa214.jpg@96w_96h_1c_1s.webp)](https://space.bilibili.com/323968201)

[陈伟国AE](https://space.bilibili.com/323968201)

粉丝：291文章：10

关注

上篇专栏介绍并提供了[ESP-IDF 4.3环境搭建教程和材料](https://www.bilibili.com/read/cv14959043?spm_id_from=333.999.0.0)

由于官方文档中已经介绍了VS和Eclipse作为IDE开发espidf的教程,本文就主要介绍如何以Clion作为开发工具来把玩ESP32系列芯片。首先懒人包发一发:

**链接：https://pan.baidu.com/s/1pK2jzQlZlhTvwUv_GF3Jgw 
提取码：ALYA**

**
**

**CLion-ESP32开发懒人包 内含:**

1. Clion 2021破解版
2. ESP32 工程模板

解压后你将得到如下文件:

![img](https://i0.hdslb.com/bfs/article/067f47a5d8e7f922b0c6dc21a6decaad50700157.png@942w_80h_progressive.webp)CLion-ESP32开发懒人包

首先介绍如何安装破解最新版的Clion



# Clion 2021 安装

**1.打开"CLion2021破解版"文件夹:**

![img](https://i0.hdslb.com/bfs/article/961c4adf09ebb2e38db31645e0718efcbf372fca.png@942w_108h_progressive.webp)CLion2021破解版文件夹

**2.运行 "CLion-2021.3.exe" 以安装Clion 2021**

![img](https://i0.hdslb.com/bfs/article/08f8064afd5be3918870a1f536dda4d9bec64cc9.png@942w_722h_progressive.webp)安装Clion

![img](https://i0.hdslb.com/bfs/article/573d4976b4263876a09f7e53240a0e76332b89e8.png@942w_722h_progressive.webp)按照上图选择

![img](https://i0.hdslb.com/bfs/article/48ca10781bbf32f7eb0939975b6b4dc3f095ab7e.png@942w_722h_progressive.webp)等待安装完成

安装完成后会提示你重启电脑,重启就完事了



**3.运行 "Clion-2021"并破解**

![img](https://i0.hdslb.com/bfs/article/cc26aa431bd018da718f7b709d8eeb3632071bb4.png@942w_563h_progressive.webp)运行Clion

点击Activation code 输入激活码破解

![img](https://i0.hdslb.com/bfs/article/4a86593be7cb61d264c44d6b02f61028228c60f0.png@942w_561h_progressive.webp)在此输入激活码

激活码在txt里面,直接复制,如果激活码无效,可以在txt中的网址中获取最新的激活码

![img](https://i0.hdslb.com/bfs/article/60afa4a08344908dccfe1fe93cb29da2eb35cf9b.png@942w_95h_progressive.webp)打开 破解方案(优先使用) txt

复制到文本框里,如果激活码可用就是绿色的,然后点击Activate激活

![img](https://i0.hdslb.com/bfs/article/44e2b4e896990a3328d62f4d371ede066dc14b19.png@942w_569h_progressive.webp)点击Activate

激活成功将看到此界面,然后点Close

![img](https://i0.hdslb.com/bfs/article/303d8776120daa4dfa15445e97dae632cf51a286.png@942w_566h_progressive.webp)激活成功

新建工程以验证Clion是否破解成功

![img](https://i0.hdslb.com/bfs/article/2169b06f6fd4465f0afba75deb3f72e14438483b.png@942w_708h_progressive.webp)新建个工程试试

新建工程成功后不需要做任何配置,比如Mingw编译器也不用配置,现在最新版Clion会自动检测帮你完成编译器下载和配置,等待其构建完成即可。

构建完成后,跑个Hello World试试看

![img](https://i0.hdslb.com/bfs/article/fe03fa5ae3af48270c83ed81ff1cc91687dc83ea.png@942w_603h_progressive.webp)Hello World测试

点击Help->About可以查看你Clion的授权时长,可以看到已经激活到了公元5000年12月31日,直接给你激活到人类灭亡。

![img](https://i0.hdslb.com/bfs/article/03eb7a1ac165aff027878366b349b2488bd4579c.png@942w_680h_progressive.webp)激活验证





# Clion ESP32环境配置

**1.打开esp-idf安装目录并复制此路径:**

![img](https://i0.hdslb.com/bfs/article/9aac9639f8008c311bad6e4bf3f700cd9f55c872.png@942w_714h_progressive.webp)复制esp-idf安装路径

打开cmd并cd此路径(右键粘贴)

![img](https://i0.hdslb.com/bfs/article/d59d89cdd61f2eb620d1df634e4576a948da1980.png@942w_491h_progressive.webp)cmd cd并进入此路径

输入 **export.bat**

![img](https://i0.hdslb.com/bfs/article/87adcc696c46db546af2d556c13f3e807231e366.png@942w_492h_progressive.webp)输入export.bat

**2.输入\**echo %PATH%\**复制如下路径**

紧接着输入 **echo %PATH%**

![img](https://i0.hdslb.com/bfs/article/7ff40a17f298689d80c5eca2884601f480f7c8cb.png@942w_494h_progressive.webp)输入 echo %PATH%

复制如下路径,到时候要配置到系统环境变量中 (右键复制)

![img](https://i0.hdslb.com/bfs/article/9307fa7594d2ab2ed6379ed19cc04d084d2f7b79.png@942w_492h_progressive.webp)复制此路径

**3.在系统变量中选中Path行并编辑**

![img](https://i0.hdslb.com/bfs/article/55ce785816faa3f5da66b1b9b69505fca32ac5cc.png@942w_923h_progressive.webp)编辑系统变量Path行

点击编辑文本

![img](https://i0.hdslb.com/bfs/article/4cf0011e1669bcc81e445c1d4b48da91f8de6021.png@942w_924h_progressive.webp)点击编辑文本

**注意这里操作有些许细节,仔细观看**

**(1) 把光标移动到文本末尾位置**

![img](https://i0.hdslb.com/bfs/article/b972fb609039d5b295eb39afcaa2c307c268eace.png@942w_245h_progressive.webp)移动光标到这行文本最后

**(2) 输入一个 " ; " 作为分隔符 (分号)**

![img](https://i0.hdslb.com/bfs/article/ef04a78bd8018e680604062dffdaa5fdf9f1c4d3.png@942w_242h_progressive.webp)末尾输入一个分号

**(3) 把刚才复制的路径粘贴到分后后面**

![img](https://i0.hdslb.com/bfs/article/855b7450f550ddf5380d786bed662532bdeac41d.png@942w_239h_progressive.webp)粘贴刚才的路径

点击确定,可以看到添加了很多新行

![img](https://i0.hdslb.com/bfs/article/151619af51ca9590dc6e3abc320580b162352fcd.png@942w_930h_progressive.webp)如上图,增加了不少新行

**(4) (重点操作) 把Python310这行移动到最后一行(十分重要)**

点击下移按钮移动到最后一行

![img](https://i0.hdslb.com/bfs/article/c57723229d666fbd2dbd7cea7c28a2f42957c9e1.png@942w_927h_progressive.webp)将Python310下移到最后一行

将Python310移动到最后一行

![img](https://i0.hdslb.com/bfs/article/a0b08201d4fadb9e1c5a0857bd3d12e9af1af9f3.png@942w_929h_progressive.webp)注意上图,把Python310移动到最后一行

原因简单解释一下,esp-idf在构建项目时会根据所需的工具去寻找系统环境变量配置的路径,当然是顺序查询的,所以会存在先后关系,比如idf文件夹中自带的python环境和之前你安装的Python310,如果Python310在前面,那么idf就会选此路径作为python环境构建,结果当然会构建失败,所以得把Python310移动到idf自带的py下面,这样一来既能让idf获取到正确的构建环境又能保证不影响你之前搭建的Python环境。



**4.再次复制esp-idf安装路径**

![img](https://i0.hdslb.com/bfs/article/9aac9639f8008c311bad6e4bf3f700cd9f55c872.png@942w_714h_progressive.webp)复制此路径

**5.在系统变量中新建系统变量**

新建 **IDF_PATH** 系统变量

值为 你刚才复制的路径

点击确定

![img](https://i0.hdslb.com/bfs/article/b16dec2fd5e90f79b962ad4bfcf820abc4093ea8.png@942w_876h_progressive.webp)新建 IDF_PATH 系统变量

如下图所示

![img](https://i0.hdslb.com/bfs/article/8cffa598ea8fdcb8b16cb5cc09d88793bc284a2e.png@942w_479h_progressive.webp)新建完毕

**6.重启电脑**

配置完上面一系列的系统变量后需要重启电脑

![img](https://i0.hdslb.com/bfs/article/e41f7a7b43784ac31c3fa5af78fa6968fada6137.png@942w_464h_progressive.webp)重启电脑



重启后,打开懒人包中的**ESP32工程文件**,并用Clion打开**sample_project**项目

![img](https://i0.hdslb.com/bfs/article/a6bc1091deeea8ab48e0b8fd3ee8017fc005d0d0.png@942w_110h_progressive.webp)打开ESP32工程文件



用CMake project 打开

![img](https://i0.hdslb.com/bfs/article/286f902912d3eb958e699c74f64ecd2394a492c1.png@593w_371h_progressive.webp)选择CMake project

点击Trust Project

![img](https://i0.hdslb.com/bfs/article/83f7a9240dcddf03bb987818a391fbd0a37438dc.png@938w_434h_progressive.webp)点Trust Project

打开后Clion会开始加载Cmake,等待完成后你就可以Build了,右上角的锤子会变绿

![img](https://i0.hdslb.com/bfs/article/f9e81cb42104096cab0709976d2c425ae5aa8452.png@942w_504h_progressive.webp)Clion打开ESP32项目

**7. 点击右上角锤子构建项目** (2022/2/26日更新 串口监视器配置)

点锤子构建,注意不要点小三角,那是运行按钮,需要配置一个可执行文件,因为此项目生成的elf(Executable and Linkable file 用于生成bin文件)在Windows无法运行,所以跑不起来,会报一个elf无法运行的错误。不过你可以发挥你的聪明才智,将此可执行文件选为串口调试工具,那么以后你每次运行完毕都会自动打开串口调试工具。当然esp-idf也提供了串口监视器命令,你只需自己配置一个bat文件,用于在CLion的命令行中运行串口监视器,就像这样:

**注意,如果你不想在CLion中配置串口监视器就可以跳过了,直接跳到分隔符之后**

<--------------------------------------------------我是起始符------------------------------------------------>

![img](https://i0.hdslb.com/bfs/article/ba46dae5633e152c4ae82f87ae2cfed3c2f54c25.png@942w_531h_progressive.webp)

然后将run configuration中的executable选为你这个bat文件

![img](https://i0.hdslb.com/bfs/article/4d2d7f591be099450cb2dfc74f6f22259e9b126b.png@861w_1572h_progressive.webp)点Edit Configurations进去

![img](https://i0.hdslb.com/bfs/article/f846e01c96c3d5473793fcb8aaf7db2ea170be81.png@942w_437h_progressive.webp)配置操作

至于为什么要选到flash项,因为串口监视器只有在程序烧进去之后运行才有意义,你想配置app项或者其他项目，原理是一样的。

注意要更改下Cmake的输出路径,因为idf.py monitor会去寻找..\build路径下的elf文件,若找不到就会报elf not found的错误。

Clion中进入File->Settings->Build,Execution,Deployment->CMake

![img](https://i0.hdslb.com/bfs/article/9de0a25c6ed5c74212dd00e111797e2fd049e786.png@942w_681h_progressive.webp)千万别忘了build文件夹

配置完后,点击绿色小三角运行,除了构建之外,Clion会执行你刚才创建的bat文件,如下:

![img](https://i0.hdslb.com/bfs/article/00186b036fcf795d95bcea5ed511bcfefb0d8b7a.png@942w_324h_progressive.webp)运行效果

由于手头没有板子,所以只能演示个无法连接到串口了。

连接着板子的话,此程序会主动连接对应串口,并打印串口消息。(我感觉没什么用,还不如另外跑一个sscom来的爽)

<--------------------------------------------------我是结束符------------------------------------------------>



第一次构建需要几分钟,900多个文件需要编译链接,后续就只需要编译自己写的c/c++文件了。不过后续如果你对构建配置做了任何修改,都需要重新构建,再编译一次900多个文件。

![img](https://i0.hdslb.com/bfs/article/e42ee9d1d30f09f5936858a46c6c72949c1b713d.png@942w_506h_progressive.webp)构建完成

下面介绍一下esp32工程的几个构建选项

![img](https://i0.hdslb.com/bfs/article/78aed5e10febbbb29aba855fb870c806b155147d.png@867w_1257h_progressive.webp)构建选项

下面我将分别演示**app,flash和menuconfig选项**



**(1) app选项**

选择app并点击锤子构建

![img](https://i0.hdslb.com/bfs/article/22bb4bacf4ca6d60808741aca6ed58370c0c957b.png@834w_62h_progressive.webp)下拉菜单选为app

可以看到app选项下**生成了main.bin文件 ,** 可以将此文件下载到ESP32上

![img](https://i0.hdslb.com/bfs/article/68a9033d5d53da505fe69db9f968ef35988a3aa9.png@942w_506h_progressive.webp)生成了bin文件

**(2) flash选项**

1.先连接上esp32板子,我演示采用esp-12k开发板(内部芯片esp32-s2)

2.打开设备管理器或者串口工具**查询开发板端口号**,我是COM4

![img](https://i0.hdslb.com/bfs/article/1b5e3202e877b5c350c736e431368d348b08baf4.png@429w_72h_progressive.webp)查询开发板端口号

3.Clion中进入File->Settings->Build,Execution,Deployment->CMake

![img](https://i0.hdslb.com/bfs/article/ee5dbb1f1a3aabfc5afff916db4a33946262ae7e.png@942w_684h_progressive.webp)打开此界面

4.在Environment中输入: 

**ESPBAUD=460800;ESPPORT=COM4;IDF_TARGET=esp32s2**

意味着下载波特率为460800,端口号为COM4,芯片型号为esp32s2

![img](https://i0.hdslb.com/bfs/article/ade7796c20530290c1ebaa4361065a12e4517d4c.png@942w_684h_progressive.webp)输入环境变量

输入完成后,点apply再点OK退出

![img](https://i0.hdslb.com/bfs/article/d27f7b1341c8ee5ff266af1fa2ce0b41fd342198.png@942w_686h_progressive.webp)列表查看

然后Cmake构建报了个cache does not match的错误

![img](https://i0.hdslb.com/bfs/article/5a0d1cc252671328241f7bf47cc3b70bfddeb437.png@942w_506h_progressive.webp)小问题

**点击Tools->CMake->Reset Cache and Reload Project**

![img](https://i0.hdslb.com/bfs/article/10d3311d0f097094ef1b9b6b0b8b2cc9588b1eb3.png@942w_315h_progressive.webp)没手就行

好了,不报错了

![img](https://i0.hdslb.com/bfs/article/2c5382fb3a608fcf5cafdd1151098ee708f35e1b.png@942w_506h_progressive.webp)水一张图

5.写一个Hello World,烧到板子里可以看到效果

![img](https://i0.hdslb.com/bfs/article/220bf4a7973bd4ef0334b92eb9a10b2ec0d92287.png@942w_353h_progressive.webp)水一个Hello World

6.选择flash并点击锤子构建

![img](https://i0.hdslb.com/bfs/article/d6ede5b4f230c92b67d9c719801dff897fbd9c58.png@833w_60h_progressive.webp)下拉菜单选为flash然后锤他

由于刚才修改了构建配置,所以又得重新把那900个文件编译一遍了,慢慢等吧

![img](https://i0.hdslb.com/bfs/article/d7f4768fa5bef5cee3b269754c4443a6e028f450.png@942w_506h_progressive.webp)再水一张图

OK,下载成功,打开串口监视器看看效果

![img](https://i0.hdslb.com/bfs/article/4e5b19a1f95e9718aff7ac9c06a848e3a32b052b.png@942w_384h_progressive.webp)下载成功

注意esp32串口波特率默认为115200,看到不断输出 Hello World!

![img](https://i0.hdslb.com/bfs/article/6b7d0c9f4f1d5765698cad8a05a460b2c574c4ba.png@942w_716h_progressive.webp)下载验证成功

总结一下flash选项的要点:

1.根据你对应的芯片配置IDF_TARGET变量

2.根据你的端口号配置ESPPORT变量

3.然后再点锤子构建



**(3) menuconfig选项**

此选项用于配置ESP32芯片的一些核心参数,包括主频,晶振频率,分区表,下载相关参数,本文仅介绍如何打开esp32配置面板

1.用cmd打开你的项目目录

![img](https://i0.hdslb.com/bfs/article/d8a0d883b3116bbc5bfba321772c9f1578494cef.png@942w_507h_progressive.webp)cmd打开项目目录

输入 **idf.py menuconfig**

![img](https://i0.hdslb.com/bfs/article/c3a0ec9e8b911cbf912386de1c9d5d254fd54677.png@942w_497h_progressive.webp)cmd输入idf.py menuconfig

等待一会后就进入了esp32配置面板,具体使用参考官方文档,一般情况下使用不到,若下载失败或下载成功后芯片串口报错,很可能是app太大了,请注意在此修改下flash size

![img](https://i0.hdslb.com/bfs/article/ccf90d36e3906be79df3ba24f2d38d0f1b6c0ecb.png@942w_504h_progressive.webp)esp32配置面板

总结下,系统环境变量配置那一部分请严格按照教程走,配置无误的话,用Clion打开工程将不会有任何报错,可以直接构建。此教程中的所有配置和图片均在一台未安装任何环境的电脑中演示并截取。若按照此文配置出现差错,直接评论私信我,立刻解决并更新文中错误。



最后,放一个esp32经典入门程序:

```javascript
#include <sys/cdefs.h>
#include "sdkconfig.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

_Noreturn void app_main(void)
{
    //初始化nvs存储器
    nvs_flash_init();
    //初始化TCP/IP堆栈,一定要调用此函数,不然DHCP无法运行(因为它基于UDP协议)
    tcpip_adapter_init();
    /**
     * esp_event_loop_create_default()
     * 请务必不要忘记创建默认事件循环,以下为官方文档解释
     * Wi-Fi事件处理基于esp_event库。Wi-Fi驱动程序会将事件发送到默认事件循环。
     * 某些 ESP-NETIF API 函数旨在由应用程序代码调用，例如获取/设置接口 IP 地址、配置 DHCP。
     * 在许多情况下，应用程序不需要直接调用 ESP-NETIF API，因为它们是从默认网络事件处理程序中调用的。
     *
     * 也就是说,如果不创建默认事件循环,WiFi事件触发后,将不会产生默认处理。例如,有人连入你的热点,即产生
     * 热点连入事件,但由于你没有创建默认事件循环,自然不会通过DHCPS为此人分配IP地址。那么此时你就需要自己
     * 调用esp-netif库函数来启动DHCP服务器分配IP地址了,已踩坑,配置十分复杂。
     **/
    esp_event_loop_create_default();
    //初始化WiFi参数(默认参数)
    wifi_init_config_t initConfig=WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&initConfig);
    //设置WiFi模式,STA+AP模式
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    //设置热点信息,这里只设置了热点名和密码
    wifi_config_t wifiConfig={.ap={
            "我是热点名",
            "12345678",
            .max_connection=10,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
    }};
    //热点模式,配置为上结构体属性
    esp_wifi_set_config(ESP_IF_WIFI_AP,&wifiConfig);
    //启动WiFi
    esp_wifi_start();

    while(true){
        printf("测试\r\n");
    }
}
```

很简单的程序,演示了如何用esp32打开一个热点并简要演示了esp32 wifi开发流程

![img](https://i0.hdslb.com/bfs/article/01e1f1d57244f07c2ae223447d80ca48cbd031b9.png@942w_506h_progressive.webp)下载到板子里

WiFi列表中发现ESP32的热点了,看看连进去能不能通过DHCPS分配到IP地址

![img](https://i0.hdslb.com/bfs/article/b4253ce05f0d833e2c4cf11f7cb5aa0fdef1f340.png@681w_1089h_progressive.webp)查看WiFi列表

输入密码测试连接

![img](https://i0.hdslb.com/bfs/article/630a6f8b0134b75ebf8110f91b3052ba37978764.png@678w_332h_progressive.webp)输入密码

连接测试成功

![img](https://i0.hdslb.com/bfs/article/57c2f3e13f775e5a9483751fc62dea4e95b42b09.png@942w_1104h_progressive.webp)测试成功

只要严格按照教程配置,绝对能一遍通,至于为什么推荐Clion开发,因为我Stm32也在Clion开发,同样也发布了[教程](https://www.bilibili.com/read/cv11442303?spm_id_from=333.999.0.0),刚好凑一个系列。最主要还是多个芯片集成在一个IDE中开发比较爽。