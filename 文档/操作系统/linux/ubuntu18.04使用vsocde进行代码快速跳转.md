环境：

ubuntu18

vsocde+clangd插件

clangd

bear

## clangd下载：

不要直接sudo apt-get install，版本太低用起来有问题，不能够正确识别跳转

**添加LLVM官方APT源**：

首先，添加LLVM的GPG密钥：

```
bash


复制编辑
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
```

然后，添加LLVM的APT源到您的软件源列表中。对于Ubuntu 18.04（代号`bionic`），可以使用以下命令：

```
bash


复制编辑
sudo add-apt-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main"
```

更新软件包列表后，您就可以安装更新版本的`clangd`了。例如，安装`clangd-12`：

```
bash复制编辑

sudo apt update
sudo apt install clangd-12
```

安装完成后，您可以通过之前提到的`update-alternatives`命令来设置默认的`clangd`版本。



### 上面失败，换个安装方式，这里安装clangd19

```
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh
sudo apt install clangd
clangd --version
```



## bear下载：

### 安装依赖

1. 更新 PPA 依赖库

   ```
   bash复制编辑
   sudo add-apt-repository ppa:savoury1/build-tools -y
   sudo add-apt-repository ppa:savoury1/backports -y
   sudo apt-get update
   ```

2. 尝试安装缺失的依赖项

   ```
   bash
   
   
   复制编辑
   sudo apt-get install libear libgrpc++1 -y
   ```

   如果这些库仍然无法安装，说明 PPA 中可能没有 Ubuntu 18.04 的支持。

### 使用 PPA 仓库

Bear 的官方包在 Ubuntu 18.04 中的版本为 2.3.11。要获取更新版本，可以使用第三方 PPA 仓库。以下是使用 Rob Savoury 提供的 PPA 仓库安装 Bear 3.1.4 的步骤：

1. **安装 Bear：**

   ```
   bash
   
   
   复制编辑
   sudo apt-get install bear -y
   ```


通过上述步骤，您将安装 Bear 的 3.1.4 版本。

## vsocde+clangd插件

注意下载好clangd插件后，会提示禁用c/c++智能感知引擎，这个和clangd有冲突

### 配置clangd插件

进入设置，搜索：

```
@ext:llvm-vs-code-extensions.vscode-clangd
```

为Clangd: Arguments项添加参数

```
--compile-commands-dir=${workspaceFolder}
--background-index
--completion-style=detailed
--header-insertion=never
--log=inf
```

为Clangd: Path项添加参数，这个参数时clangd的位置，

使用

```
 whereis clangd
```

可以知道

```
/usr/bin/clangd
```

或者直接在settings.json中添加：

```
    "clangd.arguments": [
        "--compile-commands-dir=${workspaceFolder}",
        "--background-index",
        "--completion-style=detailed",
        "--header-insertion=never",
        "--log=info"
    ],
    "clangd.path": "/usr/bin/clangd"
```

## 创建compile_commands.json文件

在编译内核的make之前加入bear --，可生成compile_commands.json文件，例如

```
bear -- make xxx
```

等待编译完成

在当前工作文件夹中添加链接文件，

```
ln -s  ~/Desktop/ebf_linux_kernel/compile_commands.json ./compile_commands.json
```

其中

```
~/Desktop/ebf_linux_kernel/compile_commands.json
```

是上述生成的compile_commands.json文件位置，./compile_commands.json是当前工作目录

## 在工作目录添加额外项

### 添加.clangd文件

用于给clangd识别--gcc-toolchain位置

```
CompileFlags:
  Add: [-target, arm-linux-gnueabihf, --gcc-toolchain=/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf]
```

## 开始创建索引

在vscode中，ctrl+p后：

```
clangd.restart
```

点击后等待创建完毕，vscode下方状态栏会有进度信息

