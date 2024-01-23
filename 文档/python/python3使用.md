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



## 高级特性

简化代码数量，相当于语法糖

### 切片：":"

场景：取一个list或tuple的部分元素是非常常见的操作。这时，就可以使用切片。

例子：有一个list，对其切片

```
list_list = []
for num in range(0, 10):
    list_list.append(num)
print(list_list)
# 头一个到倒数第二个
print(list_list[:-1])
# 第三个到倒数第二个
print(list_list[2:-1])
```

输出得到

```
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
[0, 1, 2, 3, 4, 5, 6, 7, 8]
[2, 3, 4, 5, 6, 7, 8]
```



## 内建函数

### open

用于打开文件：一般使用方式为：

```
open(file_name, "r")
```

后面跟的字符串"r"，表示打开方式，常用打开方式有：

| r    | 以只读方式打开文件。文件的指针将会放在文件的开头。这是默认模式。 |
| ---- | ------------------------------------------------------------ |
| w    | 打开一个文件只用于写入。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。 |
| a    | 追加写入，打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。 |

详细可见：

[菜鸟教程]: https://www.runoob.com/python/python-func-open.html



### 迭代





#### 补充读写文件注意项

读写文件时，open文件后要记得关闭，在python中提供了相应的语法糖：**with**，一般使用方法为：

```python
# 打开一个文件，遍历文件每行，并输出
with open(file_new_name, "r+") as file:
    for line_file in file:
        print(line_file)
```

上述方式，在遇到文件比较大时，可能导致爆内存，大文件推荐使用临时文件读取

```py
input_filename = "file_name"
output_filename = "out_" + input_filename
with open(input_filename, "r") as input_file, open(output_filename, "a") as output_file:
    for line in input_file:
        # 在每一行前添加 "=="
        modified_line = "==\n" + line
        output_file.write(modified_line)
```

上述方式不仅读了大文件，还对大文件每行进行了写操作。

直接在原文件上遍历写的话，可能比较复杂，chatgpt没有给出完美的解决方案，可能干的人少，理由是：源文件直接写，中途的错误，可能会直接导致源文件数据的丢失和损坏。



以下有一种每行读并写入文本的错误操作方式：

```py
with open(file_new_name, "r+") as file:
    for line_file in file:
        print(line_file)
        # file.flush()
        file.write("test===")
        file.write("test2===")
```

运行后得到文件：

```
asdfsdf
asdfsdf
asdfsdfsdf
test===test2===
```

而且控制台输出只有第一行：asdfsdf，后面就直接运行结束了，出现这个想想的可能原因，chatgpt回答：

```
在Python中，您的代码片段试图在使用'r+'模式打开文件时，一边读取文件内容一边进行写入操作。然而，这种方法可能会导致问题，因为'r+'模式的文件操作并不是严格的“读取再写入”操作，它涉及了文件指针的位置和缓冲区的管理，这可能会导致意外的结果。

特别是在处理大文件时，同时进行读写操作可能会导致文件指针位置混乱，内容被覆盖，甚至文件损坏。此外，缓冲区的管理也可能会导致一些数据在写入之前仍然在内存中，而不会立即写入到文件中。
```





# 高级编程部分
