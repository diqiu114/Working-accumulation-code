关于采用**MobaXterm_Portable_v23.2**去连接ubutun的步骤

首先得确定虚拟机linux和window是否连通

在win10cmd找到Linux ip

![image-20230718160758573](linux%E5%AD%A6%E4%B9%A0.assets/image-20230718160758573.png)

这里是

```
192.168.220.1
```

ping通，证明连接没有问题

![image-20230718160900516](linux%E5%AD%A6%E4%B9%A0.assets/image-20230718160900516.png)

去设置win10下的虚拟网络编辑器，要用管理员运行

这里直接参考韦东山的嵌入式linux应用开发完全手册即可

然后需要查看linux下是否已经启动ssh服务

一般需要先安装ssh服务

使用

```
sudo apt-get install openssh-server
```

有时这里会提示依赖问题，比如

```
The following packages have unmet dependencies:
 openssh-server : Depends: openssh-client (= 1:7.2p2-4ubuntu2.8)
                  Depends: openssh-sftp-server but it is not going to be installed
                  Recommends: ssh-import-id but it is not going to be installed
E: Unable to correct problems, you have held broken packages.
```

根据他的提示去解决即可

```
sudo apt-get install openssh-client=1:7.2p2-4ubuntu2.8
```

安装完成后，启用ssh服务

```
sudo /etc/init.d/ssh start
```

查看是否真的开启成功

```
ps -e|grep ssh 
```

返回，出现ssh表示启用成功

```
yzq-linux@ubuntu:/etc/ssh$ ps -e|grep ssh 
   1710 ?        00:00:00 ssh-agent
   9664 ?        00:00:00 sshd
  10196 ?        00:00:00 sshd
  10198 ?        00:00:00 sshd
  10321 ?        00:00:00 sshd
  10336 ?        00:00:00 sshd
  10582 ?        00:00:00 sshd
  10584 ?        00:00:00 sshd
  10680 ?        00:00:00 sshd
  10713 ?        00:00:00 sshd
```

后续怎么使用MobaXterm_Portable连接linux按部就班的按照韦东山的教程来即可











# 一些命令

## 系统相关

```
systemctl

当使用systemctl命令打印服务状态时，输出的各项含义如下：

UNIT：显示服务单元的名称，即服务的标识符。

LOAD：显示服务单元文件的加载状态。可能的状态有：

loaded：服务单元文件已加载，但服务未运行。
not-found：未找到对应的服务单元文件。
disabled：服务单元文件存在，但被禁用。
ACTIVE：显示服务的活动状态。可能的状态有：

active：服务正在运行。
inactive：服务未运行。
activating：服务正在启动过程中。
deactivating：服务正在停止过程中。
failed：服务启动失败。
SUB：显示服务的子状态。子状态是活动状态的更详细描述。

DESCRIPTION：显示服务的描述，通常提供服务的简要说明。

VENDOR PRESET：显示服务是否由系统或软件包的供应商预设的启用或禁用状态。如果显示 "enabled" 或 "disabled"，则表示是预设的状态；如果显示 "-"，则表示没有预设状态。

总的来说，使用systemctl命令可以查看系统中所有服务的状态，包括服务是否加载、是否在运行、是否被禁用以及服务的简要说明。这些信息对于管理和监控系统的运行状态非常有用。
```

```

systemctl list-unit-files --type=service

各个项的含义如下：

UNIT FILE：这一列显示了服务的名称，即服务单元文件的名称。这些单元文件通常位于 /lib/systemd/system/ 和 /etc/systemd/system/ 目录下。

STATE：这一列表示服务的当前状态。可能的状态包括：

enabled：服务已启用，将在系统启动时自动启动。
disabled：服务已禁用，不会在系统启动时自动启动。
static：服务已启用，但不会自动启动，只能通过其他方式（例如依赖关系）启动。
masked：服务被掩盖，禁止启动。
generated：服务由系统动态生成。
VENDOR PRESET：这一列表示服务由系统或软件包的供应商预设的启用或禁用状态。如果显示 "enabled" 或 "disabled"，则表示是预设的状态；如果显示 "-"，则表示没有预设状态。

请注意，通过这个命令输出的列表，您可以看到当前系统中所有已安装服务的状态，其中包括自启动的服务。
```







## 虚拟机挂载开发板的nfs目录

目的：这样就可以直接在虚拟机上操作开发板的目录

步骤：

1. 首先确认虚拟机能ping通开发板

2. 确认nfs服务开启，两个linux都要开启

   通过查看：

   ```
   sudo systemctl status nfs-kernel-server
   ```

   如果服务没有运行，可以使用以下命令启动它：

   ```
   sudo systemctl start nfs-kernel-server
   ```

​		如果没有安装，通过使用`apt`命令进行安装：

```
sudo apt update
sudo apt install nfs-common       # NFS客户端
sudo apt install nfs-kernel-server  # NFS服务器
```

3. 创建挂载目录和被挂载目录

4. 查看nfs服务器被挂载目录的权限

   ```
   sudo vi /etc/exports
   ```

5. **配置正确的共享选项**：在 `/etc/exports` 文件中，确保已正确设置共享目录的配置。一个示例的配置可能是：（目录和权限）

   ```
   /home/orangepi/nfs_rootfs  192.168.3.2(rw,sync,no_subtree_check)
   ```

如果挂载失败，可以通过

```
sudo cat /var/log/syslog | grep nfs
```

查看日志





## 怎么挂载？

sudo mount 服务器ip地址:被挂载的文件夹 用于本机访问的文件夹

```
sudo mount 192.168.3.2:/home/orangepi/nfs_rootfs /home/yzq-linux/Desktop/mnt
```
