报错：

```
Err:1 http://us.archive.ubuntu.com/ubuntu focal InRelease                   
  Connection failed [IP: 10.0.0.1 80]
```

此时能够获取到谷歌网页信息，证明网络和代理都没有问题

```
yzq-linux@ubuntu:/etc$ wget http://www.google.com
--2023-07-16 23:29:59--  http://www.google.com/
Connecting to 192.168.134.1:7316... connected.
Proxy request sent, awaiting response... 302 Found
Location: http://www.google.com.hk/url?sa=p&hl=zh-CN&pref=hkredirect&pval=yes&q=http://www.google.com.hk/&ust=1689575429624417&usg=AOvVaw39kM5OtZNh5bxwPTK3DvWi [following]
--2023-07-16 23:29:59--  http://www.google.com.hk/url?sa=p&hl=zh-CN&pref=hkredirect&pval=yes&q=http://www.google.com.hk/&ust=1689575429624417&usg=AOvVaw39kM5OtZNh5bxwPTK3DvWi
Reusing existing connection to 192.168.134.1:7316.
Proxy request sent, awaiting response... 302 Found
Location: http://www.google.com.hk/ [following]
--2023-07-16 23:30:00--  http://www.google.com.hk/
Reusing existing connection to 192.168.134.1:7316.
Proxy request sent, awaiting response... 200 OK
Length: unspecified [text/html]
index.html: Permission denied

```

百度得知，可能是dns原因

打开dns配置：

```
 code /etc/resolv.conf
```

更换nameserver为谷歌公用dns8.8.8.8

```
nameserver 8.8.8.8
```

测试，问题解决

```
yzq-linux@ubuntu:/etc$ sudo apt-get update
Get:1 http://us.archive.ubuntu.com/ubuntu focal InRelease [265 kB]          
Get:2 http://security.ubuntu.com/ubuntu focal-security InRelease [114 kB]
Get:3 http://us.archive.ubuntu.com/ubuntu focal-updates InRelease [114 kB]
Get:4 http://us.archive.ubuntu.com/ubuntu focal-backports InRelease [108 kB]
Get:5 http://security.ubuntu.com/ubuntu focal-security/main i386 Packages [620 kB]
Get:6 http://us.archive.ubuntu.com/ubuntu focal/main amd64 Packages [970 kB]
Get:7 http://us.archive.ubuntu.com/ubuntu focal/main i386 Packages [718 kB]
```

