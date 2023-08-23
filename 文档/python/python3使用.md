# 语法和杂七杂八

## _xx、xx__ 区别

```
_xx、__xx、__xx__ 区别
_xx：表示变量波保护，不希望外部访问，但可以访问到
__xx：表示变量私有，只有内部能访问到
__xx__：
类似 __xx__ 或 __xx__() 这种前后都有 2 个下划线的变量或方法，通常是Python中内置的特殊变量属性或方法的标识，我们应尽量避免使用该方式来自定义变量或方法
一般情况下，Python代码执行时会自动调用到这些内置属性或方法，比如当一个类对象实例化时，就会自动调用 __new__() 和 __init__() 来完成构造和初始化。
```



## 空语句

**pass**



## 中文

加u，例如：

```
print(u"=======当前路径：" + os.getcwd())
```



# pip遇到的问题

## 出现：  ERROR: Failed building wheel for pysilk-mod

前提说明：

```
  Stored in directory: /home/orangepi/.cache/pip/wheels/de/bd/bd/4aca667b1b66ffdc66ec328ca3510b1d7470ed5c1da4e1ce85
  Building wheel for pysilk-mod (PEP 517) ... error
  ERROR: Command errored out with exit status 1:
   command: /usr/bin/python3 /tmp/tmphi0rgjds build_wheel /tmp/tmp55zglwv3
       cwd: /tmp/pip-install-7is1l2di/pysilk-mod
  Complete output (31 lines):
  running bdist_wheel
  running build
  running build_py
  creating build
  creating build/lib.linux-aarch64-cpython-38
  creating build/lib.linux-aarch64-cpython-38/pysilk
  copying src/pysilk/wav.py -> build/lib.linux-aarch64-cpython-38/pysilk
  copying src/pysilk/utils.py -> build/lib.linux-aarch64-cpython-38/pysilk
  copying src/pysilk/pysilk.py -> build/lib.linux-aarch64-cpython-38/pysilk
  copying src/pysilk/__main__.py -> build/lib.linux-aarch64-cpython-38/pysilk
  copying src/pysilk/__init__.py -> build/lib.linux-aarch64-cpython-38/pysilk
  running egg_info
  writing src/pysilk_mod.egg-info/PKG-INFO
  writing dependency_links to src/pysilk_mod.egg-info/dependency_links.txt
  writing top-level names to src/pysilk_mod.egg-info/top_level.txt
  reading manifest file 'src/pysilk_mod.egg-info/SOURCES.txt'
  adding license file 'LICENSE'
  writing manifest file 'src/pysilk_mod.egg-info/SOURCES.txt'
  running build_ext
  aarch64-linux-gnu-gcc -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security -g -fwrapv -O2 -fPIC -I/usr/include/python3.8 -c flagcheck.cpp -o flagcheck.o -std=c++17
  building 'pysilk.coder' extension
  creating build/temp.linux-aarch64-cpython-38
  creating build/temp.linux-aarch64-cpython-38/src
  creating build/temp.linux-aarch64-cpython-38/src/silk
  creating build/temp.linux-aarch64-cpython-38/src/silk/src
  aarch64-linux-gnu-gcc -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security -g -fwrapv -O2 -fPIC -DVERSION_INFO=1.6.2 -Isrc/silk/interface -I/tmp/pip-build-env-qqgovn4b/overlay/lib/python3.8/site-packages/pybind11/include -I/usr/include/python3.8 -c src/silk/src/SKP_Silk_warped_autocorrelation_FIX.c -o build/temp.linux-aarch64-cpython-38/src/silk/src/SKP_Silk_warped_autocorrelation_FIX.o -fvisibility=hidden -g0
  src/silk/src/SKP_Silk_warped_autocorrelation_FIX.c:28:10: fatal error: SKP_Silk_main_FIX.h: No such file or directory
     28 | #include "SKP_Silk_main_FIX.h"
        |          ^~~~~~~~~~~~~~~~~~~~~
  compilation terminated.
  error: command '/usr/bin/aarch64-linux-gnu-gcc' failed with exit code 1
  ----------------------------------------
  ERROR: Failed building wheel for pysilk-mod

```

很显然，他是在构建时发现没有SKP_Silk_main_FIX.h这个文件然后停下的。

试去是来没作用，然后在lssues下网友提议，使用：

```
pip uninstall silk-python && pip install git+https://github.com/DCZYewen/Python-Silk-Module
```

这句命令表示执行以下操作：

1. 首先，使用`pip uninstall`命令卸载名为`silk-python`的软件包。
2. 然后，使用`pip install`命令从GitHub上安装一个名为`Python-Silk-Module`的软件包。它是从指定的GitHub仓库（https://github.com/DCZYewen/Python-Silk-Module）中安装的。

完美解决这个包构建问题









# 教程学习

## list和tuple

```
# 列表
list = ["list1", "list2", "list3"]
# 元组，初始化后元素就不可更改，单元素指向的数据可以改，只有一个元素时要注意加","
tuple = ("tuple", )
tuple2 = ("tuple2", ["list1", "list2"])
tuple2[1][1] = "list3"
```

## dict

```
# dict（map），查找键对应值，这是一种高效的方法，以空间换时间，不会随着列表变长而变长
map = {"xiaoming":"daxia", "xiaohong":"caiji"}
# 直接提取时，当没有该键，就会报错
print(map["xiaoming"])
# 使用get方法，返回none，或指定为-1
print(map.get("caiji"))
print(map.get("caiji")==None)
print(map.get("caiji", -1))
```

## 函数

```
# ******函数
# 定义了一个函数，在函数定义时，默认参数L会实例化
def add_end(L=[]):
    L.append('END')
    return L

# 有一个list
func_list = [1, 2, 3]
# 添加进去，但是，函数add_end中的L指向了func_list
add_end(func_list)
print(func_list)

# 空参数，L就是定义时的L
func_list2 = add_end()

add_end(func_list)
print(func_list)

# L再次被添加'END'
func_list3 = add_end()
# func_list3填充为：['END', 'END']
print(func_list3)
```

注意：**默认参数**

```
# 用不变对象None，再返回，就不会产生
def add_end(L=None):
    if L==None:
        L = []
    L.append('END')
    return L

func_list2 = add_end()
func_list3 = add_end()
print(func_list2)
print(func_list3)
```

