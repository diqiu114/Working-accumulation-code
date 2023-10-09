[VSCode作为终端工具替代FinalShell和MobaXterm](https://blognas.hwb0307.com/skill/1248)

 [Bensz](https://blognas.hwb0307.com/author/huangwb8)

 

|

 

 2022-6-01 16:55

 

|

 

 2,383

 

|

 

 [技能](https://blognas.hwb0307.com/category/skill)



 2327 字

 

|

 

 11 分钟

本文最后更新于 236 天前，如有失效请评论区留言。

> 有需要可加**[电报群](https://t.me/benszhub)**获得更多帮助。本博客用什么**[VPS](https://blognas.hwb0307.com/ad)**？创作不易，请**[支持](https://blognas.hwb0307.com/thankyou)**苯苯！推荐购买本博客的**[VIP](https://blognas.hwb0307.com/subscribe)**喔，10元/年即可畅享所有VIP专属内容！也欢迎大佬对本文进行**[慈善承包](https://blognas.hwb0307.com/enterprise)**(ฅ´ω`ฅ)

# 前言

> 我以前在淘宝买过一个Mobaxterm中文绿色版，不嫌弃的话可以从[这里](https://nextcloud.hwb0307.com/s/tWK5pqxyBbjYFxW)下载。

不知小伙伴们都用过哪些终端工具？我有用过XShell、FinalShell、MobaXterm和[tabby](https://github.com/Eugeny/tabby/releases)，它们各有各的特点，特别是MobaXterm，我觉得是比较完美的终端工具。不过，今天和小伙伴们讨论的时候，发现**VSCode也可以作为一个终端工具**：



![NVIDIA_Share_98VlgjxGCW](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_98VlgjxGCW.webp)



所以有点按捺不住那颗想要折腾的心了！

而且，我们可以**直接利用VSCode本地编辑器对远程文件进行预览和编辑**，这应该是VSCode作为终端工具的最大卖点之一吧：



![NVIDIA_Share_X781dZVOcf](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_X781dZVOcf.webp)



此外，你甚至可以用来预览png等图片！一般的终端工具应该是做不到的：



![NVIDIA_Share_0CsdDAOWIq](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_0CsdDAOWIq.webp)



我平时使用Python的时候就会使用VSCode；VSCode本身也是一个比较流行的IDE。我个人喜欢VSCode的主要原因是因为**VSCode兼容性好、插件功能强大、颜值高**，比较适合我这种编程小白。初步体验了一下它的SSH功能，效果不错！如果你本来就在使用VSCode，它也可以作为一个终端工具喔！你也不用纠结要用Final Shell还是MobaXterm了！

这一期我们不讲怎么安装VSCode，大家可以在官网下载并安装即可：[VSCode下载](https://code.visualstudio.com/Download)。对于Windows系统的用户来说，和安装一般的`.exe`软件没有太大的区别。我主要讲（shui）一下**怎么将VSCode打造成一个远程访问VPS的终端工具**。

# 安装Remote-SSH扩展

首先，我们要在本地VSCode客户端上安装一个VSCode的扩展，叫`Remote - SSH`。它的主要作用就是提供ssh访问的基本功能：



![NVIDIA_Share_kGS8Ylju88](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_kGS8Ylju88.webp)



成功安装后，左侧栏中会出现一个电脑显示器的图标。依下图所示打开config文件（对Windows用户来说，路径一般是`C:\Users\Administrator\.ssh\config`），进行相关的设置：



![NVIDIA_Share_GEl2lB4END](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_GEl2lB4END.webp)



内容类似于：

```
Host 主机1
  HostName 192.168.1.151
  User user1
  Port 22
 
Host 主机2
  HostName 192.168.1.152
  User user3
  Port 1452
 
Host 主机3
  HostName 192.168.1.153
  User user3
  Port 3355
```

以`主机1`为例，参数解释如下：

- **Host**：主机的名字。随便取，只为了自己识别方便。
- **HostName**：通常是一个ip地址，可以是公网ip；如果是访问局域网机器，就写一个局域网ip。
- **User**：用户名
- **Port**：ssh端口。默认是22；如果你的VPS自定义了ssh端口，比如1234，就使用1234。

加几台主机就会显示几台主机，没有数量限制。注意，**不需要填写密码**。

# VSCode Proxy

值得一提的是，**VSCode支持在访问主机的时候添加代理**，这对于远程访问国外VPS的小伙伴来说可能是有益的。只需要（ProxyCommand结尾的`127.0.0.1:10809`即本地代理，请按需更改）：

```
Host 主机1
  HostName <某远程VPS的ip地址/解析域名>
  User user1
  Port 22
  ProxyCommand C:\\Program Files\\Git\\mingw64\\bin\\connect.exe -H 127.0.0.1:10809 %h %p
```

这里的`connect.exe`来自于Git，因此你需要在本地电脑提前安装Git。只需要简单地在`Everything`里搜索一下即可快速定位：



![NVIDIA_Share_xJXP7knXw6](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_xJXP7knXw6.webp)



当然，还有一些其它方案，可见：[Remote SSH: Tips and Tricks](https://code.visualstudio.com/blogs/2019/10/03/remote-ssh-tips-and-tricks)。但此法需要一个跳板机，实现过程不够简洁，故并不推荐。

此外，**VSCode本身也是可以设置代理的**！这个属于题外话，但也许有人也是需要的！如果你想开启VSCode全局代理，只需要按`F1`并打开`用户设置(JSON)`：



![NVIDIA_Share_Vh65fsdfAt](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_Vh65fsdfAt.webp)



然后，在某个独立的位置添加如下记录即可（后面的逗号最好不要忽略喔）：

```json
"http.proxy": "http://127.0.0.1:10809",

 
 
 
```

# 在VPS上添加本地公钥

不太推荐登陆时使用密码，直接让远程的VPS信任本地主机就好。一般来说，如果你的电脑里用过ssh服务的话，`.ssh`文件夹里都会有这两个文件：

```
id_rsa
id_rsa.pub
```

如果没有这两个文件，对Windows用户而言，可以用管理员权限打开cmd或者Power Shell，输入`ssh-keygen`，按提示操作即可生成这两个文件。`id_rsa`是私钥，只能保存在本地电脑，不可让其它人知道；`id_rsa.pub`是公钥，保存在远程VPS中，让其它人知道也无所谓（一般也只是自己知道啦）。

这时，如果你想要通过访问某VPS中的某个用户，要先利用该用户的身份登陆VPS，进入用户的home目录，然后将`id_rsa.pub`的内容添加到该用户的`.ssh`文件夹里的`authorized_keys`文件里，类似于：



![NVIDIA_Share_hxJWLKdWvI](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_hxJWLKdWvI.webp)



这样，**远程VPS就会信任我们的本地电脑，访问的时候就不需要密码了**。

如果这个用户没有`.ssh`和`authorized_keys`这两个文件（如果从来没设置过，一般是没有的），可以手动创建，然后运行命令`sudo service sshd restart`重启ssh服务生效。

让VPS信任我们的本地电脑后，我们直接右键某条SSH记录，直接点击`Open on SSH Host in Current Window`（在本窗口访问）或者`Open on SSH Host in New Window`（在新窗口访问）：



![NVIDIA_Share_qf354cZKRk](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_qf354cZKRk.webp)



即可正常访问。登陆成功后，左下角会出现`SSH:主机1`之类的字样。

第一次连接时，由于需要在VPS端安装`vscode sever`，所以时间会略长。之后登陆速度就会蛮快的了。

# 打开Shell

默认情况下，按`Ctrl+j`就可以调出Shell，再按一次`Ctrl+j`就会隐藏Shell。按右边的`^`图案可以向上填充Shell。这个是VScode的常规操作，与Remote SSH并无直接关联。



![NVIDIA_Share_d21QzxaioH](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_d21QzxaioH.webp)



# 选择目录

有时候，我们想进入某个目录对某个文件进行编辑。默认情况下，你可以按`Ctrl+k+o`就可以调出目录选择；按`Esc`就可以退出选择。通常，你可以选择一个高级目录，比如根目录`/`，这样就不需要频繁地切换目录。VSCode每次切换这个工作目录都要重新连接一次。

当然，你编辑文件的时候，权限来自之前`authorized_keys`所对应的用户的权限。比如你登陆的是一个普通用户，是没有办法直接读写或执行root用户的文件的（除非root给予你相应的权限）。



![NVIDIA_Share_D6VtfsztMz](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_D6VtfsztMz.webp)



# 上传文件

如果你要上传文件，直接拉到目录里就行了，这和大多数终端工具的行为是类似的：



![NVIDIA_Share_0CsdDAOWIq](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_0CsdDAOWIq.webp)



# 无法登陆？

我今天在自己的NAS里就遇到无法用VSCode登陆的情况。经过一翻调查，这通常是由于**系统里没有VSCode的下载源**所致的。我们按以下步骤进行解决：

- 通过root权限将`/etc/ssh/sshd_config`文件中的`AllowTcpForwarding`设定为yes。
- 重启ssh服务：`sudo service sshd restart`
- 删除旧的VSCode文件夹：`rm -rf .vscode-server/`
- 安装好VSCode源（以Debian系的Linux发行版为例）：

```bash
# 下载必要软件
sudo apt-get install software-properties-common apt-transport-https curl
 
# 下载微软的asc文件
curl -sSL https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
 
# 添加仓库
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
 
# 更新软件列表
sudo apt update
```

最后，再重新通过本地的VSCode去连接此VPS或NAS，则可成功。

# 小结

设置其实也不难，就是安装一个拓展。VSCode本身也是一个强大的工具，以后有机会再多多介绍吧！我先试用一段时间，之后会陆续反馈体验效果！

# 日志

## 2022-10-28

添加VSCode Proxy的相关教程。

## 2022-06-08

实际使用中，登陆速度、响应速度、文件下载速度均不及Mobaxterm等传统SSH软件，感觉功能还有很大的改进空间。有点噱头的感觉！大家玩一下可以，暂时还不推荐将VScode当作主力SSH连接工具。

## 2022-06-05

进一步讨论和测试后，发现本地使用VSCode的SSH时，VPS端也会相应地调用vscode-server，这导致一定的内存和cpu使用，对VPS性能造成微小的损失。**不同系统的占用程度略有不同**。比如，我的NAS使用的是OpenMediaVault，vscode-server的CPU占用就比较高；而Ubuntu里面的占用就比较低。如果你准备使用vscode server，且VPS配置比较低的话，使用VSCode作为SSH终端工具还是要考虑再三。



![NVIDIA_Share_YMcaWuZbcm](%E4%BD%BF%E7%94%A8ssh%E4%BD%9C%E4%B8%BA%E7%BB%88%E7%AB%AF%E5%B7%A5%E5%85%B7.assets/NVIDIA_Share_YMcaWuZbcm.webp)



## 2022-06-03

偶尔出现ssh连接速度略慢，不像MobaXterm那样可以秒开。可能是因为需要在remote端加载vscode设置有关。可以用，但不完美。连接成功后倒是蛮稳定的。

# 参考

- [Remote SSH via Visual Studio Code](https://forum.openmediavault.org/index.php?thread/40505-remote-ssh-via-visual-studio-code/)
- [SSH to OMV5 via VSCode](https://www.reddit.com/r/OpenMediaVault/comments/qyhta6/ssh_to_omv5_via_vscode/)
- [Vscode源使用帮助](https://help.shuosc.org/vscode.html)
- [如何在Debian 10安装vscode](https://www.myfreax.com/how-to-install-visual-studio-code-on-debian-10/)

\---------------
*完结，撒花！如果您点一下广告，可以养活苯苯*😍😍😍