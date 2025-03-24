

## 仓库地址

```
remote.origin.url=https://github.com/Embedfire/ebf_linux_kernel.git
branch.ebf_4.19.35_imx6ul.remote=origin
branch.ebf_4.19.35_imx6ul.merge=refs/heads/ebf_4.19.35_imx6ul
branch.ebf_4.19.35_imx6ul.vscode-merge-base=origin/ebf_4.1.15_imx
```



## 设置静态ip

新版 Debian（特别是 Debian 9 及更新版本）默认使用 **`systemd-networkd` 或 `NetworkManager`** 来管理网络，而不是 `/etc/network/interfaces` 文件。

野火的用的是systemd-networkd

## **使用 `ip link` 确认网卡名称**

有些系统网卡名称可能不是 `eth2`，先检查：

```
bash


复制编辑
ip link show
```

如果 `eth2` 存在，就继续下一步。如果网卡名称不同，请替换下面配置中的 `eth2`。



## **方法 1：使用 `systemd-networkd`（推荐）**

你的系统可能使用 `systemd-networkd` 来管理网络，按以下步骤配置：

### **1. 创建网络配置文件**

```
sudo nano /etc/systemd/network/eth2.network
```

然后写入以下内容：

```
[Match]
Name=eth2

[Network]
Address=192.168.7.71/24
Gateway=192.168.7.1
DNS=8.8.8.8 8.8.4.4
```

**保存并退出（Ctrl+X → Y → Enter）**

### **2. 重新启动 `systemd-networkd`**

```
bash


复制编辑
sudo systemctl restart systemd-networkd
```

检查 `eth2` 是否获得了静态 IP：

```
bash


复制编辑
ip a show eth2
```

**如果 `eth2` 还是没有 IP，尝试以下命令：**

```
bash复制编辑sudo systemctl enable systemd-networkd
sudo reboot
```

## 编译内核注意事项：

要用根目录下的

```
make_deb.sh
```

用make_lite.sh不对

编译完成后，内核源码要用

```
KERNELDIR = xx/ebf_linux_kernel/build_image/build
```

