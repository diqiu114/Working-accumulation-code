## 搭建前准备

1. vscode

   1. vscode插件clangd

      安装完成后，在扩展设置中的 Clangd: Arguments进行设置

      ```
      --compile-commands-dir=${workspaceFolder}
      --background-index
      --completion-style=detailed
      --header-insertion=never
      -log=info
      ```

      ```
      -log=info嫌打印信息太多的话可以设置为error
      ```

2. linux内核源码

3. bear

   ```
   sudo apt install bear
   ```

## 内核开发

安装好后切入到linux内核，去编译内核，这里用的clangd插件实现的代码跳转，而代码跳转依赖的是

```
compile_commands.json
```

而bear生成这个文件，只需要在编译内核的时候，在命令前加上bear，比如：

```
bear make 。。。。。。
```

在野火中，是用.sh文件写的只需要

```
deb_distro=bionic
DISTRO=stable
build_opts="-j 12"
build_opts="${build_opts} O=build_image/build"
build_opts="${build_opts} ARCH=arm"
build_opts="${build_opts} KBUILD_DEBARCH=${DEBARCH}"
build_opts="${build_opts} LOCALVERSION=-carp-imx6"
build_opts="${build_opts} KDEB_CHANGELOG_DIST=${deb_distro}"
build_opts="${build_opts} KDEB_PKGVERSION=1${DISTRO}"
build_opts="${build_opts} CROSS_COMPILE=arm-linux-gnueabihf-" 	
build_opts="${build_opts} KDEB_SOURCENAME=linux-upstream"
make ${build_opts}  npi_v7_defconfig
bear make ${build_opts}   #加在这
make ${build_opts}  bindeb-pkg
```

然后生成的compile_commands.json文件，需要手动替换文本里的内容

```
[
    {
        "arguments": [
            "cc",
            "-c",
            "-Wp,-MD,drivers/net/wireless/broadcom/brcm80211/brcmutil/.brcmutil.mod.o.d",
            "-nostdinc",
            "-isystem",
            。。。。。。。。。。。。。。。
```

把里头的cc全部替换为编译器，比如

换成

```
[
    {
        "arguments": [
            "arm-linux-gnueabihf-gcc",
            "-c",
            "-Wp,-MD,drivers/net/wireless/broadcom/brcm80211/brcmutil/.brcmutil.mod.o.d",
            "-nostdinc",
            "-isystem",
            。。。。。。。。。。。。。。。
```



然后在源码目录添加上面生成的compile_commands.json文件的软链接到当前源码目录

```
ln -s /home/yzq-linux/Desktop/ebf_linux_kernel/compile_commands.json ./compile_commands.json
```

在vscode的配置json中加上这个文件

arm v7可能会报错，在workspace目录下创建一个.clangd文件，写入

```
CompileFlags:
  Add: --target=armv7-a
```

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
   cmake_minimum_required (VERSION 3.1)
   
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

