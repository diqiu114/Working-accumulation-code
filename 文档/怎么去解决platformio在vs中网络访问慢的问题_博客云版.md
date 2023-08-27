官方文档说：

![image-20230704100140626](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124128027-1087854625.png)

![image-20230704100150470](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124128396-819804643.png)

去看platfrom core说用的是py底层`requests`库来处理 HTTP 请求

![image-20230704100332645](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124127785-653202206.png)

解决方法：设置两个系统环境变量：

形式为：

```
HTTP_PROXY:http://代理地址:端口
HTTPS_PROXY:http://代理地址:端口
```

在clash中怎么找代理地址和端口？

![image-20230704100849863](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124127906-2125129675.png)

![image-20230704100939582](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124127816-1984812629.png)

![image-20230704101520292](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124128420-2131883637.png)

![image-20230704101143456](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124127852-226947610.png)

**测试：**

win的shell输入

```
curl https://www.google.com
```

已经没问题了：

![image-20230704101252290](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124128421-1822403774.png)

platformio中搜索库能够快速打开

![image-20230704101817914](https://img2023.cnblogs.com/blog/2501991/202307/2501991-20230723124127945-762248406.png)





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







**声明：转发请注明出处**
