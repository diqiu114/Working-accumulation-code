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









# 工具集合

# Tmux 使用教程

作者： [阮一峰](https://www.ruanyifeng.com/)

日期： [2019年10月21日](https://www.ruanyifeng.com/blog/2019/10/)

**Tmux** 是一个终端复用器（**terminal multiplexe**r），非常有用，属于常用的开发工具。

本文介绍如何使用 Tmux。

![img](linux%E5%AD%A6%E4%B9%A0.assets/bg2019102005.png)

## 一、Tmux 是什么？

### 1.1 会话与进程

命令行的典型使用方式是，打开一个终端窗口（terminal window，以下简称"窗口"），在里面输入命令。**用户与计算机的这种临时的交互，称为一次"会话"（session）** 。

会话的一个重要特点是，窗口与其中启动的进程是[连在一起](https://www.ruanyifeng.com/blog/2016/02/linux-daemon.html)的。打开窗口，会话开始；关闭窗口，会话结束，会话内部的进程也会随之终止，不管有没有运行完。

一个典型的例子就是，[SSH 登录](https://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html)远程计算机，打开一个远程窗口执行命令。这时，网络突然断线，再次登录的时候，是找不回上一次执行的命令的。因为上一次 SSH 会话已经终止了，里面的进程也随之消失了。

为了解决这个问题，会话与窗口可以"解绑"：窗口关闭时，会话并不终止，而是继续运行，等到以后需要的时候，再让会话"绑定"其他窗口。

### 1.2 Tmux 的作用

**Tmux 就是会话与窗口的"解绑"工具，将它们彻底分离。**

> （1）它允许在单个窗口中，同时访问多个会话。这对于同时运行多个命令行程序很有用。
>
> （2） 它可以让新窗口"接入"已经存在的会话。
>
> （3）它允许每个会话有多个连接窗口，因此可以多人实时共享会话。
>
> （4）它还支持窗口任意的垂直和水平拆分。

类似的终端复用器还有 GNU Screen。Tmux 与它功能相似，但是更易用，也更强大。

## 二、基本用法

### 2.1 安装

Tmux 一般需要自己安装。

> ```bash
> # Ubuntu 或 Debian
> $ sudo apt-get install tmux
> 
> # CentOS 或 Fedora
> $ sudo yum install tmux
> 
> # Mac
> $ brew install tmux
> ```

### 2.2 启动与退出

安装完成后，键入`tmux`命令，就进入了 Tmux 窗口。

> ```bash
> $ tmux
> ```

上面命令会启动 Tmux 窗口，底部有一个状态栏。状态栏的左侧是窗口信息（编号和名称），右侧是系统信息。

![img](linux%E5%AD%A6%E4%B9%A0.assets/bg2019102006.png)

按下`Ctrl+d`或者显式输入`exit`命令，就可以退出 Tmux 窗口。

> ```bash
> $ exit
> ```

### 2.3 前缀键

Tmux 窗口有大量的快捷键。所有快捷键都要通过前缀键唤起。默认的前缀键是`Ctrl+b`，即先按下`Ctrl+b`，快捷键才会生效。

举例来说，帮助命令的快捷键是`Ctrl+b ?`。它的用法是，在 Tmux 窗口中，先按下`Ctrl+b`，再按下`?`，就会显示帮助信息。

然后，按下 ESC 键或`q`键，就可以退出帮助。

## 三、会话管理

### 3.1 新建会话

第一个启动的 Tmux 窗口，编号是`0`，第二个窗口的编号是`1`，以此类推。这些窗口对应的会话，就是 0 号会话、1 号会话。

使用编号区分会话，不太直观，更好的方法是为会话起名。

> ```bash
> $ tmux new -s <session-name>
> ```

上面命令新建一个指定名称的会话。

### 3.2 分离会话

在 Tmux 窗口中，按下`Ctrl+b d`或者输入`tmux detach`命令，就会将当前会话与窗口分离。

> ```bash
> $ tmux detach
> ```

上面命令执行后，就会退出当前 Tmux 窗口，但是会话和里面的进程仍然在后台运行。

`tmux ls`命令可以查看当前所有的 Tmux 会话。

> ```bash
> $ tmux ls
> # or
> $ tmux list-session
> ```

### 3.3 接入会话

`tmux attach`命令用于重新接入某个已存在的会话。

> ```bash
> # 使用会话编号
> $ tmux attach -t 0
> 
> # 使用会话名称
> $ tmux attach -t <session-name>
> ```

### 3.4 杀死会话

`tmux kill-session`命令用于杀死某个会话。

> ```bash
> # 使用会话编号
> $ tmux kill-session -t 0
> 
> # 使用会话名称
> $ tmux kill-session -t <session-name>
> ```

### 3.5 切换会话

`tmux switch`命令用于切换会话。

> ```bash
> # 使用会话编号
> $ tmux switch -t 0
> 
> # 使用会话名称
> $ tmux switch -t <session-name>
> ```

### 3.6 重命名会话

`tmux rename-session`命令用于重命名会话。

> ```bash
> $ tmux rename-session -t 0 <new-name>
> ```

上面命令将0号会话重命名。

### 3.7 会话快捷键

下面是一些会话相关的快捷键。

> - `Ctrl+b d`：分离当前会话。
> - `Ctrl+b s`：列出所有会话。
> - `Ctrl+b $`：重命名当前会话。

## 四、最简操作流程

综上所述，以下是 Tmux 的最简操作流程。

> 1. 新建会话`tmux new -s my_session`。
> 2. 在 Tmux 窗口运行所需的程序。
> 3. 按下快捷键`Ctrl+b d`将会话分离。
> 4. 下次使用时，重新连接到会话`tmux attach-session -t my_session`。

## 五、窗格操作

Tmux 可以将窗口分成多个窗格（pane），每个窗格运行不同的命令。以下命令都是在 Tmux 窗口中执行。

### 5.1 划分窗格

`tmux split-window`命令用来划分窗格。

> ```bash
> # 划分上下两个窗格
> $ tmux split-window
> 
> # 划分左右两个窗格
> $ tmux split-window -h
> ```

![img](linux%E5%AD%A6%E4%B9%A0.assets/bg2019102007.jpg)

### 5.2 移动光标

`tmux select-pane`命令用来移动光标位置。

> ```bash
> # 光标切换到上方窗格
> $ tmux select-pane -U
> 
> # 光标切换到下方窗格
> $ tmux select-pane -D
> 
> # 光标切换到左边窗格
> $ tmux select-pane -L
> 
> # 光标切换到右边窗格
> $ tmux select-pane -R
> ```

### 5.3 交换窗格位置

`tmux swap-pane`命令用来交换窗格位置。

> ```bash
> # 当前窗格上移
> $ tmux swap-pane -U
> 
> # 当前窗格下移
> $ tmux swap-pane -D
> ```

### 5.4 窗格快捷键

下面是一些窗格操作的快捷键。

> - `Ctrl+b %`：划分左右两个窗格。
> - `Ctrl+b "`：划分上下两个窗格。
> - `Ctrl+b <arrow key>`：光标切换到其他窗格。`<arrow key>`是指向要切换到的窗格的方向键，比如切换到下方窗格，就按方向键`↓`。
> - `Ctrl+b ;`：光标切换到上一个窗格。
> - `Ctrl+b o`：光标切换到下一个窗格。
> - `Ctrl+b {`：当前窗格与上一个窗格交换位置。
> - `Ctrl+b }`：当前窗格与下一个窗格交换位置。
> - `Ctrl+b Ctrl+o`：所有窗格向前移动一个位置，第一个窗格变成最后一个窗格。
> - `Ctrl+b Alt+o`：所有窗格向后移动一个位置，最后一个窗格变成第一个窗格。
> - `Ctrl+b x`：关闭当前窗格。
> - `Ctrl+b !`：将当前窗格拆分为一个独立窗口。
> - `Ctrl+b z`：当前窗格全屏显示，再使用一次会变回原来大小。
> - `Ctrl+b Ctrl+<arrow key>`：按箭头方向调整窗格大小。
> - `Ctrl+b q`：显示窗格编号。

## 六、窗口管理

除了将一个窗口划分成多个窗格，Tmux 也允许新建多个窗口。

### 6.1 新建窗口

`tmux new-window`命令用来创建新窗口。

> ```bash
> $ tmux new-window
> 
> # 新建一个指定名称的窗口
> $ tmux new-window -n <window-name>
> ```

### 6.2 切换窗口

`tmux select-window`命令用来切换窗口。

> ```bash
> # 切换到指定编号的窗口
> $ tmux select-window -t <window-number>
> 
> # 切换到指定名称的窗口
> $ tmux select-window -t <window-name>
> ```

### 6.3 重命名窗口

`tmux rename-window`命令用于为当前窗口起名（或重命名）。

> ```bash
> $ tmux rename-window <new-name>
> ```

### 6.4 窗口快捷键

下面是一些窗口操作的快捷键。

> - `Ctrl+b c`：创建一个新窗口，状态栏会显示多个窗口的信息。
> - `Ctrl+b p`：切换到上一个窗口（按照状态栏上的顺序）。
> - `Ctrl+b n`：切换到下一个窗口。
> - `Ctrl+b <number>`：切换到指定编号的窗口，其中的`<number>`是状态栏上的窗口编号。
> - `Ctrl+b w`：从列表中选择窗口。
> - `Ctrl+b ,`：窗口重命名。

## 七、其他命令

下面是一些其他命令。

> ```bash
> # 列出所有快捷键，及其对应的 Tmux 命令
> $ tmux list-keys
> 
> # 列出所有 Tmux 命令及其参数
> $ tmux list-commands
> 
> # 列出当前所有 Tmux 会话的信息
> $ tmux info
> 
> # 重新加载当前的 Tmux 配置
> $ tmux source-file ~/.tmux.conf
> ```

## 八、参考链接

- [A Quick and Easy Guide to tmux](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/)
- [Tactical tmux: The 10 Most Important Commands](https://danielmiessler.com/study/tmux/)
- [Getting started with Tmux](https://linuxize.com/post/getting-started-with-tmux/)

# exa

[exa](https://the.exa.website/) is a modern replacement for *ls*.

**README Sections:** [Options](https://github.com/ogham/exa#options) — [Installation](https://github.com/ogham/exa#installation) — [Development](https://github.com/ogham/exa#development)

[![Unit tests](linux%E5%AD%A6%E4%B9%A0.assets/badge.svg+xml)](https://github.com/ogham/exa/actions/workflows/unit-tests.yml) [![Say thanks!](linux%E5%AD%A6%E4%B9%A0.assets/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f5361792532305468616e6b732d212d3145414544422e737667.svg+xml)](https://saythanks.io/to/ogham%40bsago.me)

[![Screenshots of exa](linux%E5%AD%A6%E4%B9%A0.assets/screenshots.png)](https://github.com/ogham/exa/blob/master/screenshots.png)

------

**exa** is a modern replacement for the venerable file-listing command-line program `ls` that ships with Unix and Linux operating systems, giving it more features and better defaults. It uses colours to distinguish file types and metadata. It knows about symlinks, extended attributes, and Git. And it’s **small**, **fast**, and just **one single binary**.

By deliberately making some decisions differently, exa attempts to be a more featureful, more user-friendly version of `ls`. For more information, see [exa’s website](https://the.exa.website/).

仓库链接：https://github.com/ogham/exa.git





# vim

**以下是局部设置：**

开启鼠标模式

:set mouse=x, x取值如下, 例如:set mouse=a, 开启所有模式的mouse支持

    n 普通模式
    v 可视模式
    i 插入模式
    c 命令行模式
    h 在帮助文件里，以上所有的模式
    a 以上所有的模式
    r 跳过 |hit-enter| 提示
    A 在可视模式下自动选择

关闭鼠标模式

**全局设置**：

1. 打开 Vim 配置文件： 在终端中输入以下命令来编辑 Vim 的配置文件（如果你还没有该文件，则会创建一个新文件）：

   ```
   bashCopy code
   vim ~/.vimrc
   ```

   如果你已经有了 `~/.vimrc` 配置文件，直接使用 Vim 打开它。

2. 添加鼠标支持设置： 在打开的 `~/.vimrc` 文件中添加以下设置来启用鼠标支持：

   ```
   vimCopy code
   set mouse=a
   ```

   这会将鼠标模式设置为 "a"，它包含了 Normal、Visual 和 Insert 模式的鼠标支持。



:set mouse=, =后面不要跟任何值, 可以关闭鼠标模式
-----------------------------------
©著作权归作者所有：来自51CTO博客作者码农编程进阶笔记的原创作品，如需转载，请与作者联系，否则将追究法律责任
vim鼠标模式打开与关闭
https://blog.51cto.com/lxw1844912514/3107723







# bat

由于在linux中有冲突，所以直接使用bat是没有响应的，因该使用：

这个在超出一页时，会默认管道输出到less中

```
batcat
```

使用

```
--paging=never
```

这样就不会输出到less中， 会直接显示全部内容









