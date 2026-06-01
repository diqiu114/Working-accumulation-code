生成密钥

```
ssh-keygen -t rsa
```

查看密钥是否真的生成

```
cat ~/.ssh/id_rsa.pub
```

复制到linux上后

```
mkdir -p ~/.ssh
cat ./id_rsa.pub >> ~/.ssh/authorized_keys
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
```



vscode配置文件，按这个格式配置

```
Host ubuntu20-dev       # 【连接别名，可以自定义，比如保持你的 Ubuntu20】

  HostName 192.168.164.128   # 【关键！此处必须填写虚拟机的 IP 地址】

  User ubuntu20       # 【填写你在虚拟机中的登录用户名】

  Port 22          # SSH 端口，通常为 22

  IdentityFile ~/.ssh/id_rsa  # 如果配置了密钥登录，请取消注释并指定私钥路径
```

