## 为Snapd设置代理

一般地，Linux上的一些应用程序会通过读取环境变量http_proxy和https_proxy来应用代理服务器设置，典型的有Chrome。然而，Snap比较特别，它不会从环境变量中上述环境变量中读取代理服务器设置，因此直接使用`export http_proxy=[代理服务器地址]`或`export https_proxy=[代理服务器地址]`是不起作用的。

所以得通过命令行这么干

打开clash找到：

![image-20230717111551961](snapd%E8%AE%BE%E7%BD%AE%E4%BB%A3%E7%90%86.assets/image-20230717111551961.png)![image-20230717111857138](snapd%E8%AE%BE%E7%BD%AE%E4%BB%A3%E7%90%86.assets/image-20230717111857138.png)

打开linux的shell输入

```
sudo snap set system proxy.http="http://192.168.134.1:7316"
sudo snap set system proxy.https="http://192.168.134.1:7316"
```

