## 搭建前准备

环境：

ubuntu18

vsocde+clangd插件

clangd

bear

### clangd下载：

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



### bear下载：

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

### vsocde+clangd插件

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

```
-log=info嫌打印信息太多的话可以设置为error
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

## 内核开发

### 创建compile_commands.json文件

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

### 在工作目录添加额外项

### 添加.clangd文件

用于给clangd识别--gcc-toolchain位置

```
CompileFlags:
  Add: [-target, arm-linux-gnueabihf, --gcc-toolchain=/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf]
```

### 开始创建索引

在vscode中，ctrl+p后：

```
clangd.restart
```

点击后等待创建完毕，vscode下方状态栏会有进度信息

### 注意事项

在ubuntu18中开发时发现如果正在写的源码文件夹和厂家提供的sdk包不在一个父文件夹中clangd就会不准，解决办法：

```
ln -s 需要写代码的工作文件夹 当前共同的父文件夹中
```

## app开发

### 前景提示

app开发时，使用命令

```
bear -- arm-linux-gnueabihf-gcc app_template.c -o "app_test"
```

这时候生成的`compile_commands.json`一般为：

```
[
  {
    "arguments": [
      "/usr/bin/gcc",
      "-c",
      "-o",
      "app_test",
      "app_template.c"
    ],
    "directory": "/home/ubuntu18/Desktop/linux_study/dirver/3_pinctrl/app",
    "file": "/home/ubuntu18/Desktop/linux_study/dirver/3_pinctrl/app/app_template.c",
    "output": "/home/ubuntu18/Desktop/linux_study/dirver/3_pinctrl/app/app_test"
  }
]
```

在其中的`arguments`项中并没有类似内核`compile_commands.json`文件中的

```
xxx"-I/home/ubuntu18/Desktop/ebf_linux_kernel/scripts/dtc/libfdt",xxx
```

`-I`选项能提供给clangd路径跳转

所以app开发时通过bear生成的文件进行代码跳转，这时候用cmake生成的`compile_commands.json`文件进行代码跳转

### 环境搭建

1. 安装cmake

2. vscode安装CMake Tools插件

3. 编写基本的`CMakeLists.txt`文件

   ```
   cmake_minimum_required (VERSION 3.5)
   
   project (demo)
   
   #[[
   添加编译器使用的头文件路径
   set(TOOLCHAIN_PATH "/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf")
   首先要设置编译器路径然后在${TOOLCHAIN_PATH}/bin/路径下执行
   arm-linux-gnueabihf-gcc -xc -E -v -
   只有会弹出来一大串数据，复制下#include <...> search starts here:的数据，
   填入include_directories中，示例：
   。。。。。。
   #include "..." search starts here:
   #include <...> search starts here:
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/include
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/include-fixed
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/../../../../arm-linux-gnueabihf/include
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/../arm-linux-gnueabihf/libc/usr/include
   End of search list.
   
   这样生成的compile_commands.json文件就能识别到包含的头文件了
   ]]
   set(TOOLCHAIN_PATH "/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf")
   set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-gcc)
   set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-g++)
   
   include_directories(
       ${TOOLCHAIN_PATH}/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/include
       ${TOOLCHAIN_PATH}/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/include-fixed
       ${TOOLCHAIN_PATH}/bin/../lib/gcc/arm-linux-gnueabihf/7.5.0/../../../../arm-linux-gnueabihf/include
       ${TOOLCHAIN_PATH}/bin/../arm-linux-gnueabihf/libc/usr/include
   )
   
   add_executable(app app_template.c)
   ```

4. 删除掉`clangd`生成的`.cache`文件，再`ctrl+shift+p`选择`clangd：restart xxx`，重新生成`.cache`文件

