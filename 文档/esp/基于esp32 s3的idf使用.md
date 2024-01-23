## idf安装



## idf使用

进入工程，需要选择好芯片型号，然后需要选择调试方式：

这个步骤，idf会配置一些东西，让后续调试什么的能和芯片配得上

注意，像s3这种能够内部继承jtag接口的，他使用openOCD调试，这里如果调试方式不选jtag，那么通过OpenOcd调试时，会显示打不开OpenOcd服务





## idf配置工具和构建系统

1. 项目配置工具

   使用kconfig配置，通过编写kconfig，能够得到图形化界面，然后再对图形化界面配置即可

2. 构建工具

   使用cmack作为构建系统，所以包含源码和头文件都需要编写cmakelists





# 问题点：

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

