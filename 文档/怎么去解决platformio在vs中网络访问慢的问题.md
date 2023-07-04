官方文档说：

![image-20230704100140626](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704100140626.png)

![image-20230704100150470](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704100150470.png)

去看platfrom core说用的是py底层`requests`库来处理 HTTP 请求

![image-20230704100332645](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704100332645.png)

解决方法：设置两个系统环境变量：

形式为：

```
HTTP_PROXY:http://代理地址:端口
HTTPS_PROXY:http://代理地址:端口
```

在clash中怎么找代理地址和端口？

![image-20230704100849863](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704100849863.png)

![image-20230704100939582](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704100939582.png)

![image-20230704101520292](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704101520292.png)

![image-20230704101143456](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704101143456.png)

**测试：**

win的shell输入

```
curl https://www.google.com
```

已经没问题了：

![image-20230704101252290](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704101252290.png)

platformio中搜索库能够快速打开

![image-20230704101817914](%E6%80%8E%E4%B9%88%E5%8E%BB%E8%A7%A3%E5%86%B3platformio%E5%9C%A8vs%E4%B8%AD%E7%BD%91%E7%BB%9C%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E9%97%AE%E9%A2%98.assets/image-20230704101817914.png)





本文中涉及的链接：

```
PlatformIO使用中遇到的坑：
https://nu-ll.github.io/2021/02/24/PlatformIO%E4%BD%BF%E7%94%A8%E4%B8%AD%E9%81%87%E5%88%B0%E7%9A%84%E5%9D%91/

官方文档：
https://docs.platformio.org/en/latest/core/installation/proxy-configuration.html#piocore-install-proxy-configuration	

https://docs.platformio.org/en/latest/core/installation/proxy-configuration.html#piocore-install-proxy-configuration

官方的FQA也有提到
https://community.platformio.org/t/how-to-set-a-proxy-for-platformio-cli/403/2
```

