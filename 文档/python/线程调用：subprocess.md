# [python subprocess详解](https://www.cnblogs.com/iamjianghao/p/11896564.html)

目录

- python subprocess详解
  - [简介：](https://www.cnblogs.com/iamjianghao/p/11896564.html#简介)
  - [运行python的时候，我们都是在创建并运行一个进程。像Linux进程那样，一个进程可以fork一个子进程，并让这个子进程exec另外一个程序。在Python中，我们通过标准库中的subprocess包来fork一个子进程，并运行一个外部的程序。 subprocess包中定义有数个创建子进程的函数，这些函数分别以不同的方式创建子进程，所以我们可以根据需要来从中选取一个使用。另外subprocess还提供了一些管理标准流(standard stream)和管道(pipe)的工具，从而在进程间使用文本通信。](https://www.cnblogs.com/iamjianghao/p/11896564.html#运行python的时候我们都是在创建并运行一个进程像linux进程那样一个进程可以fork一个子进程并让这个子进程exec另外一个程序在python中我们通过标准库中的subprocess包来fork一个子进程并运行一个外部的程序subprocess包中定义有数个创建子进程的函数这些函数分别以不同的方式创建子进程所以我们可以根据需要来从中选取一个使用另外subprocess还提供了一些管理标准流standard-stream和管道pipe的工具从而在进程间使用文本通信)
  - subprocess.call()
    - [示例：](https://www.cnblogs.com/iamjianghao/p/11896564.html#示例)
  - subprocess.check_call()
    - [示例：](https://www.cnblogs.com/iamjianghao/p/11896564.html#示例-1)
  - subprocess.check_output()：
    - [示例：](https://www.cnblogs.com/iamjianghao/p/11896564.html#示例-2)
  - subprocess.Popen()：
    - [Popen方法：](https://www.cnblogs.com/iamjianghao/p/11896564.html#popen方法)
    - [示例：](https://www.cnblogs.com/iamjianghao/p/11896564.html#示例-3)
    - [注意！](https://www.cnblogs.com/iamjianghao/p/11896564.html#注意)



## 简介：

运行python的时候，我们都是在创建并运行一个进程。像Linux进程那样，一个进程可以fork一个子进程，并让这个子进程exec另外一个程序。在Python中，我们通过标准库中的subprocess包来fork一个子进程，并运行一个外部的程序。 subprocess包中定义有数个创建子进程的函数，这些函数分别以不同的方式创建子进程，所以我们可以根据需要来从中选取一个使用。另外subprocess还提供了一些管理标准流(standard stream)和管道(pipe)的工具，从而在进程间使用文本通信。

## subprocess.call()

父进程等待子进程完成
返回退出信息(returncode，相当于Linux exit code)

### 示例：

```bash
>>> a = subprocess.call(['df','-hT'],shell=False)
文件系统       类型      容量  已用  可用 已用% 挂载点
/dev/vda3      xfs        80G  3.6G   77G    5% /
devtmpfs       devtmpfs  7.8G     0  7.8G    0% /dev
tmpfs          tmpfs     7.8G     0  7.8G    0% /dev/shm
tmpfs          tmpfs     7.8G  8.6M  7.8G    1% /run
tmpfs          tmpfs     7.8G     0  7.8G    0% /sys/fs/cgroup
/dev/vda6      xfs       404G  2.2G  402G    1% /data1
/dev/vda2      xfs       497M  128M  370M   26% /boot
tmpfs          tmpfs     1.5G     0  1.5G    0% /run/user/0
>>> print(a)
0    #程序返回的代码值
>>> a = subprocess.call('aaaa',shell=True)
/bin/sh: aaaa: 未找到命令
>>> 
```

------

## subprocess.check_call()

> subprocess.check_call(args, *, stdin = None, stdout = None, stderr = None, shell = False)

与call方法类似，不同在于如果命令行执行成功，check_call返回返回码0，否则抛出subprocess.CalledProcessError异常。
subprocess.CalledProcessError异常包括returncode、cmd、output等属性，其中returncode是子进程的退出码，cmd是子进程的执行命令，output为None。

### 示例：

```bash
>>> import subprocess
>>> a = subprocess.check_call('df -h',shell=True)
文件系统        容量  已用  可用 已用% 挂载点
/dev/vda3        80G  3.6G   77G    5% /
devtmpfs        7.8G     0  7.8G    0% /dev
tmpfs           7.8G     0  7.8G    0% /dev/shm
tmpfs           7.8G  8.6M  7.8G    1% /run
tmpfs           7.8G     0  7.8G    0% /sys/fs/cgroup
/dev/vda6       404G  2.2G  402G    1% /data1
/dev/vda2       497M  128M  370M   26% /boot
tmpfs           1.2G     0  1.2G    0% /run/user/0
>>> print(a)
0
>>> a = subprocess.check_call('aaaa',shell=True)
/bin/sh: aaaa: 未找到命令
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/usr/local/python3/lib/python3.6/subprocess.py", line 291, in check_call
    raise CalledProcessError(retcode, cmd)
subprocess.CalledProcessError: Command 'aaaa' returned non-zero exit status 127.
>>> 
```

------

## subprocess.check_output()：

用法与上面两个方法类似，区别是，如果当返回值为0时，直接返回输出结果，如果返回值不为0，直接抛出异常

### 示例：

```bash
>>> a = subprocess.check_output(['df','-hT'],shell=False)
>>> print(a)
b'\xe6\x96\x87\xe4\xbb\xb6\xe7\xb3\xbb\xe7\xbb\x9f       \xe7\xb1\xbb\xe5\x9e\x8b      \xe5\xae\xb9\xe9\x87\x8f  \xe5\xb7\xb2\xe7\x94\xa8  \xe5\x8f\xaf\xe7\x94\xa8 \xe5\xb7\xb2\xe7\x94\xa8% \xe6\x8c\x82\xe8\xbd\xbd\xe7\x82\xb9\n/dev/vda3      xfs        80G  3.6G   77G    5% /\ndevtmpfs       devtmpfs  7.8G     0  7.8G    0% /dev\ntmpfs          tmpfs     7.8G     0  7.8G    0% /dev/shm\ntmpfs          tmpfs     7.8G  8.6M  7.8G    1% /run\ntmpfs          tmpfs     7.8G     0  7.8G    0% /sys/fs/cgroup\n/dev/vda6      xfs       404G  2.2G  402G    1% /data1\n/dev/vda2      xfs       497M  128M  370M   26% /boot\ntmpfs          tmpfs     1.5G     0  1.5G    0% /run/user/0\n'
>>> print(str(a.rstrip(),'utf-8'))
文件系统       类型      容量  已用  可用 已用% 挂载点
/dev/vda3      xfs        80G  3.6G   77G    5% /
devtmpfs       devtmpfs  7.8G     0  7.8G    0% /dev
tmpfs          tmpfs     7.8G     0  7.8G    0% /dev/shm
tmpfs          tmpfs     7.8G  8.6M  7.8G    1% /run
tmpfs          tmpfs     7.8G     0  7.8G    0% /sys/fs/cgroup
/dev/vda6      xfs       404G  2.2G  402G    1% /data1
/dev/vda2      xfs       497M  128M  370M   26% /boot
tmpfs          tmpfs     1.5G     0  1.5G    0% /run/user/0
>>> 
```

------

## subprocess.Popen()：

subprocess模块定义了一个Popen类，通过它可以创建进程，并与其进行复杂的交互。

```haskell
class Popen(args, bufsize=0, executable=None, stdin=None,stdout=None, stderr=None, preexec_fn=None, close_fds=False, 
shell=False, cwd=None, env=None, universal_newlines=False, startupinfo=None, creationflags=0)
```

**在一些复杂场景中，我们需要将一个进程的执行输出作为另一个进程的输入。在另一些场景中，我们需要先进入到某个输入环境，然后再执行一系列的指令等。这个时候我们就需要使用到suprocess的Popen()方法。该方法有以下参数**

| **参数**           | **作用**                                                     |
| ------------------ | ------------------------------------------------------------ |
| args               | 一般是一个字符串，是要执行的shell命令内容                    |
| bufsize            | 设置缓冲，负数表示系统默认缓冲，0表示无缓冲，正数表示自定义缓冲行数 |
| stdin              | 程序的标准输入句柄，NONE表示不进行重定向，继承父进程，PIPE表示创建管道 |
| stdout             | 程序的标准输出句柄，参数意义同上                             |
| stderr             | 程序的标准错误句柄，参数意义同上，特殊，可以设置成STDOUT，表示与标准输出一致 |
| shell              | 为True时，表示将通过shell来执行                              |
| cwd                | 用来设置当前子进程的目录                                     |
| env                | 用于指定子进程的环境变量。如果env=None，则默认从父进程继承环境变量 |
| universal_newlines | 不同系统的的换行符不同，当该参数设定为true时，则表示使用\n作为换行符。 |

### Popen方法：

- 1、Popen.poll()：用于检查子进程是否已经结束。设置并返回returncode属性。
- 2、Popen.wait()：等待子进程结束。设置并返回returncode属性。
- 3、Popen.communicate(input=None)：与子进程进行交互。向stdin发送数据，或从stdout和stderr中读取数据。可选参数input指定发送到子进程的参数。Communicate()返回一个元组：(stdoutdata, stderrdata)。注意：如果希望通过进程的stdin向其发送数据，在创建Popen对象的时候，参数stdin必须被设置为PIPE。同样，如果希望从stdout和stderr获取数据，必须将stdout和stderr设置为PIPE。
- 4、Popen.send_signal(signal)：向子进程发送信号。
- 5、Popen.terminate()：停止(stop)子进程。在windows平台下，该方法将调用Windows API TerminateProcess（）来结束子进程。
- 6、Popen.kill()：杀死子进程。
- 7、Popen.stdin：如果在创建Popen对象是，参数stdin被设置为PIPE，Popen.stdin将返回一个文件对象用于策子进程发送指令。否则返回None。
- 8、Popen.stdout：如果在创建Popen对象是，参数stdout被设置为PIPE，Popen.stdout将返回一个文件对象用于策子进程发送指令。否则返回None。
- 9、Popen.stderr：如果在创建Popen对象是，参数stdout被设置为PIPE，Popen.stdout将返回一个文件对象用于策子进程发送指令。否则返回None。
- 10、Popen.pid：获取子进程的进程ID。
- 11、Popen.returncode：获取进程的返回值。如果进程还没有结束，返回None。
- 12、subprocess.call(*popenargs, **kwargs)：运行命令。该函数将一直等待到子进程运行结束，并返回进程的returncode。文章一开始的例子就演示了call函数。如果子进程不需要进行交互,就可以使用该函数来创建。
- 13、subprocess.check_call(*popenargs, **kwargs)：与subprocess.call(*popenargs, **kwargs)功能一样，只是如果子进程返回的returncode不为0的话，将触发CalledProcessError异常。在异常对象中，包括进程的returncode信息

### 示例：

```python-repl
>>> import subprocess
>>> subprocess.Popen('/apps/apache-tomcat-8.5.29/bin/startup.sh',shell=True)
<subprocess.Popen object at 0x7f3579b2dfd0>
>>> Using CATALINA_BASE:   /apps/apache-tomcat-8.5.29
Using CATALINA_HOME:   /apps/apache-tomcat-8.5.29
Using CATALINA_TMPDIR: /apps/apache-tomcat-8.5.29/temp
Using JRE_HOME:        /usr/java/jdk1.8.0_111/
Using CLASSPATH:       /apps/apache-tomcat-8.5.29/bin/bootstrap.jar:/apps/apache-tomcat-8.5.29/bin/tomcat-juli.jar
Tomcat started.

>>> popen = subprocess.Popen('tail -f /apps/apache-tomcat-8.5.29/logs/catalina.out',shell=True)
>>> 	at org.apache.tomcat.util.net.AbstractEndpoint.init(AbstractEndpoint.java:1086)
	at org.apache.tomcat.util.net.AbstractJsseEndpoint.init(AbstractJsseEndpoint.java:268)
	at org.apache.coyote.AbstractProtocol.init(AbstractProtocol.java:581)
	at org.apache.catalina.connector.Connector.initInternal(Connector.java:993)
	... 13 more

19-Nov-2019 17:05:05.020 信息 [main] org.apache.catalina.startup.Catalina.load Initialization processed in 650 ms
19-Nov-2019 17:05:05.045 信息 [main] org.apache.catalina.core.StandardService.startInternal Starting service [Catalina]
19-Nov-2019 17:05:05.045 信息 [main] org.apache.catalina.core.StandardEngine.startInternal Starting Servlet Engine: Apache Tomcat/8.5.29
19-Nov-2019 17:05:05.061 信息 [localhost-startStop-1] org.apache.catalina.startup.HostConfig.deployDirectory Deploying web application directory [/apps/apache-tomcat-8.5.29/webapps/ROOT]

KeyboardInterrupt
>>> popen.terminate()
>>> 
```

### 注意！

在shell=True这个参数，不写的时候默认是False，shell默认为/bin/sh。如果 args是一个字符串，则该字符串指定要通过shell执行的命令。
当需要设置shell=True时(当False时，arges是列表，第一个参数是shell命令，后面的都是参数',' 隔开)，须把args设为string，空格隔开，如下

```python-repl
>>> a = subprocess.Popen(['tail','-f', '/apps/apache-tomcat-8.5.29/logs/catalina.out'])
>>> a = subprocess.Popen('tail -f /apps/apache-tomcat-8.5.29/logs/catalina.out',shell=True)
```

# 另外可以看官网中对于subprocess描述

