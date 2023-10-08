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
