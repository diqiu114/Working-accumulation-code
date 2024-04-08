## Ubuntu 操作入门

### 学习路线

直接干驱动或者应用，boot工作一年改不了一次，裁剪厂家都做好了

### ubuntu分区和windows的差异：

命名sda1：a表示第一个磁盘，1表示一分区

linux是虚拟文件系统上挂在磁盘，windows是磁盘上挂在文件系统

注意：

​	![image-20240406203017812](C:\Users\YZQ\AppData\Roaming\Typora\typora-user-images\image-20240406203017812.png)

### FHS标准（约定俗成）

有些是系统启动必须有些不是

usr目录：unix software resource，不是用户目录😂

### 命令怎么看

用中括号[]括起来的表示可选，<>括起来的表示必选

## 使用nat，访问虚拟机ftp

前提，虚拟机需要有：

1. 安装ftp服务
2. 若使用sftp，则需要安装了ssh服务

教程

1. 虚拟机和物理机能ping通

2. 端口映射：找到虚拟机ip

   1. ![image-20230911135713874](linux%E5%AD%A6%E4%B9%A0.assets/image-20230911135713874.png)

   2. 管理员运行虚拟网络编辑器

   3. 端口映射到虚拟机

      ![image-20230911135820587](linux%E5%AD%A6%E4%B9%A0.assets/image-20230911135820587.png)

   4. 找到本机ip

      ![image-20230911135939920](linux%E5%AD%A6%E4%B9%A0.assets/image-20230911135939920.png)

   5. 连接sftp

      ![image-20230911140133851](linux%E5%AD%A6%E4%B9%A0.assets/image-20230911140133851.png)

      

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

# 虚拟网络管理器恢复默认值后不见了怎么办

手动添加，形如：

![image-20231211110647851](linux%E5%AD%A6%E4%B9%A0.assets/image-20231211110647851.png)

子网地址随便设

然后就可以了









# 一些命令

## 不分页输出

```
--no-pager
```

如，在git中使用

```
git --no-pager diff
```



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

### ls

```
ls -l		：打印文件信息
```

示例：

```
-rw-r--r-- 1 user users 12345 Jul 28 10:30 example.txt
```

解释：
第一段

```
-rw-r--r--
```

1. **文件类型和权限：** 第一个字符表示文件类型，其余九个字符表示文件的权限。每个权限字符对应一种操作权限，共有三种权限：读取（r）、写入（w）和执行（x）。如果文件有对应的权限，相应位置会显示对应的权限字符，否则显示 - 表示没有该权限。权限字符的位置分为三组，分别表示所有者权限、所属组权限和其他用户权限。

示例：

```
 -   rw-   r--   r--
```

第一个字符 - 表示这是一个普通文件。

第一个字符的类型分别解释：

- `-`：普通文件。例如：文本文件、图像文件等。
- `d`：目录。用于存放其他文件和目录的容器。
- `l`：符号链接（软链接）。类似于 Windows 系统的快捷方式，指向另一个文件或目录。
- `b`：块设备文件。代表块设备，例如硬盘、USB 设备等。
- `c`：字符设备文件。代表字符设备，例如串口、打印机等。
- `p`：命名管道（FIFO）。用于进程间通信的一种特殊文件类型。
- `s`：套接字（Socket）。用于进程间的网络通信。



rw- 表示所有者拥有读写权限。
r-- 表示所属组用户拥有读权限。
r-- 表示其他用户拥有读权限。

1. **硬链接计数：** 第二列是文件或目录的硬链接计数。一个硬链接是文件系统中对文件的另一个引用，硬链接计数表示有多少个硬链接指向此文件或目录。
2. **所有者和所属组：** 第三列和第四列分别是文件或目录的所有者用户名和所属组名称。这些信息用于标识哪些用户对该文件或目录具有特定的权限。
3. **文件大小：** 第五列是文件的大小，以字节为单位。对于目录，这个字段显示目录所占用的磁盘空间。
4. **修改时间：** 第六列是文件或目录的最近修改时间，表示文件内容最后一次被修改的时间。
5. **文件名或目录名：** 第七列是文件名或目录名，用于标识该项的名称。

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

5. **配置正确的共享选项**：在 `/etc/exports` 文件中，确保已正确设置共享目录的配置。一个示例的配置可能是：（目录和权限），

   ```
   /home/orangepi/nfs_rootfs  192.168.3.2(rw,sync,no_subtree_check)
   #这句话的意思是：服务器文件夹地址	客户端的ip(访问权限)
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



