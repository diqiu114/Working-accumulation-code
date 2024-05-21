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

