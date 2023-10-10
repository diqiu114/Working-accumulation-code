解决方法：CMake配置时会在输出目录（比如build目录）下生成一个compile_commands.json文件，里面包含了完整的编译命令。intelliSense可以使用该文件中的信息来实现正确的智能感知。

具体如下：

按下Ctrl+Shift+P键，在弹出的窗口中输入“C/++: Edit Configurations"，这样VSCode会自动在.vscode目录下生成一个c_cpp_properties.json文件。
打开c_cpp_properties.json，内容应该是这样的：

```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64",
        }
    ],
    "version": 4
}
```

在configurations中加一行配置如下（路径换成你自己的）：

```
"compileCommands": "${workspaceFolder}/build/compile_commands.json",
```

```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64",
            "compileCommands": "${workspaceFolder}/build/compile_commands.json"
        }
    ],
    "version": 4
}
```

如果没有compile_commands.json文件，可以：

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

如何配置为默认选项？

在项目的顶级 CMakeLists.txt 文件中设置默认选项:

```
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

