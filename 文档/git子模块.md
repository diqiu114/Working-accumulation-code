## Git添加子模块

submodule 指定对应分支
1、创建子模块时指定一个分支

通过 -b 指定对应分支

```
git submodule add -b master [URL to Git repo];
```

或者增加设置拉取后再本地文件夹名称

```
git submodule add -b master [URL to Git repo] [file name]
```

2、在.gitmodules 文件中设置分支

 其中 DbConnector 是主目录中安装的子目录的名称， stable 是对应要设置的分支名称

```
git config -f .gitmodules submodule.DbConnector.branch stable
```

3. 主目录中找到对应的子模块，切换到对应的分支

 其中 project 主项目， submoduleA 子模块， git checkout 切换到我们的对应分支，然后拉取对应分支代码

```
cd project/submoduleA
git checkout master
cd ..
git submodule foreach git pull
cd ..
```



## Git删除子模块和远程分支

 发表于 2018-09-22  更新于 2021-09-06  分类于 [Git](https://murphypei.github.io/categories/Git/)  阅读次数： 1869
 本文字数： 758  阅读时长 ≈ 1 分钟

Git子模块是一项重要功能，多用于项目之间的相互引用。Git的子模块初始化和更新都比较简单，然而删除一个子模块目前并没有很好的快速方法。本文也是在Gist上看到一个流程，因此记录一下。



### Git删除子模块

传统在在Git中，为了能够删除一个子模块，需要如下繁琐的流程：

- 在`.gitmodules`文件中删除相关记录
- 提交`.gitmodules`文件
  - `git add .gitmodules`
- 在`.git/config`中删除相关配置
- 删除暂存区数据
  - `git rm --cached path_to_submodule（末尾不加路径符）`
- 删除子模块
  - `rm -rf .git/modules/path_to_submodule（末尾不加路径符）`
- 提交修改
  - `git commit -m "Removed submodule "`
- 删除当前工作区数据（此时为未追踪数据）
  - `rm -rf path_to_submodule`

**现在Git更新了，有了`deinit`命令，流程简化如下：**

- Remove the submodule entry from .git/config
  ```
  git submodule deinit -f path/to/submodule
  ```
- Remove the submodule directory from the superproject’s .git/modules directory

  ```
  rm -rf .git/modules/path/to/submodule
  ```

  
- Remove the entry in .gitmodules and remove the submodule directory located at path/to/submodule
  
  ```
  git rm -f path/to/submodule
  ```
  
  

### Git删除远程分支

```
git push --delete <remote_name> <branch_name>
```

- **本文作者：** murphypei
- **本文链接：** https://murphypei.github.io/blog/2018/09/git-delete-submodule.html
- **版权声明：** 本博客所有文章除特别声明外，均采用 [BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/) 许可协议。转载请注明出处！

[# Git](https://murphypei.github.io/tags/Git/) [# delete](https://murphypei.github.io/tags/delete/) [# branch](https://murphypei.github.io/tags/branch/) [# 分支](https://murphypei.github.io/tags/分支/) [# submodule](https://murphypei.github.io/tags/submodule/)