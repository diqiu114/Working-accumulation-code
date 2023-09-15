我还真折腾了这个…

![img](%E6%B7%BB%E5%8A%A0markdown%E5%88%B0%E5%8F%B3%E9%94%AE%E5%BF%AB%E6%8D%B7%E9%94%AE.assets/v2-956f4c0622a6a8bd04df49cbd9f0a3ee_720w.webp)

其实就是在 HKEY_CLASSES_ROOT 下面添加一个 .md 的子项。

这是一个用记事本打开MD文件的[注册表文件](https://www.zhihu.com/search?q=注册表文件&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A335669784})：

```text
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\.md]
@="MarkdownFile"
"PerceivedType"="text"
"Content Type"="text/plain"

[HKEY_CLASSES_ROOT\.md\ShellNew]
"NullFile"=""

[HKEY_CLASSES_ROOT\MarkdownFile]
@="Markdown File"

[HKEY_CLASSES_ROOT\MarkdownFile\DefaultIcon]
@="%SystemRoot%\system32\imageres.dll,-102"

[HKEY_CLASSES_ROOT\MarkdownFile\shell]

[HKEY_CLASSES_ROOT\MarkdownFile\shell\open]

[HKEY_CLASSES_ROOT\MarkdownFile\shell\open\command]
@="%SystemRoot%\system32\NOTEPAD.EXE %1"
```

导入之后是这个效果：

![img](%E6%B7%BB%E5%8A%A0markdown%E5%88%B0%E5%8F%B3%E9%94%AE%E5%BF%AB%E6%8D%B7%E9%94%AE.assets/v2-787a13aed7d003c58b845d58a37b9828_720w.png)



如果装了其他的MD编辑器的话只要把 .md 这个项的值改成对应的类型就好了 比如我装的是 Typora 直接导入下面这个注册表文件就有我第一张图的效果了

```text
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\.md]
@="TyporaMarkdownFile"
"PerceivedType"="text"
"Content Type"="text/plain"

[HKEY_CLASSES_ROOT\.md\ShellNew]
"NullFile"=""
```