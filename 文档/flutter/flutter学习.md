



提示：

flutter：Error connecting to the service protocol: failed to connect to

解决办法，找到和手机对应的安卓版本，重新运行：似乎不是他引起的230801，应该是系统环境变量中设置了代理变量导致的





# flutter安装



# 开始在 Windows 上构建 Flutter Android 应用

[Flutter 起步教程](https://flutter.cn/docs/get-started)[安装和环境配置](https://flutter.cn/docs/get-started/install)[Windows](https://flutter.cn/docs/get-started/install/windows)[Android app](https://flutter.cn/docs/get-started/install/windows/mobile)

目录

- 系统要求
  - [硬件要求](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#hardware-requirements)
  - [软件要求](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#software-requirements)
- [配置文本编辑器或 IDE](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#configure-a-text-editor-or-ide)
- [安装 Flutter SDK](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#install-the-flutter-sdk)
- 配置 Android 开发
  - [在 Android Studio 中配置 Android toolchain](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#configure-the-android-toolchain-in-android-studio)
  - [配置目标 Android 设备](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#configure-your-target-android-device)
  - [同意 Android 许可证](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#agree-to-android-licenses)
- 检查你的开发配置
  - [运行 Flutter doctor](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#run-flutter-doctor)
  - [解决 Flutter doctor 的问题](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#troubleshoot-flutter-doctor-issues)
- [管理 Flutter SDK](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#manage-your-flutter-sdk)

*error* **重点提醒：**

请按顺序完成本指南。跳过步骤可能会导致错误。

## 系统要求

在安装和运行 Flutter 前，你的 Windows 环境必须满足以下要求：

### 硬件要求

你的 Windows Flutter 开发环境必须满足以下最低硬件要求。

| 要求                 |       最低        |       推荐        |
| :------------------- | :---------------: | :---------------: |
| x86_64 CPU 核心数    |         4         |         8         |
| 内存 (GB)            |         8         |        16         |
| 显示器分辨率（像素） | WXGA (1366 x 768) | FHD (1920 x 1080) |
| 可用磁盘空间 (GB)    |       10.0        |       10.0        |

### 软件要求

要为 mobile 编写和编译 Flutter 代码，你必须安装以下版本的 Windows 以及所列出的软件包。

#### 操作系统

Flutter 支持 64-bit version of Microsoft Windows 10 或更高版本。这些版本的 Windows 必须包含 [Windows PowerShell](https://docs.microsoft.com/powershell/scripting/install/installing-windows-powershell) 5.0 或更高版本。

#### 开发工具

下载并安装以下软件包的 Windows 版本：

- [Git for Windows](https://gitforwindows.org/) 2.27 或更高的版本来管理源代码。
- [Android Studio](https://developer.android.com/studio/install) 2023.1 (Hedgehog) 调试和编译 Android 的 Java 或 Kotlin 代码。 Flutter 需要完整版本的 Android Studio.

上述软件的开发商为这些产品提供支持。如果需要排除安装的问题，请查阅该产品的文档。

当你在当前版本运行 `flutter doctor` 的时候，它可能会列出这些软件包的其他不同版本。如果出现这种情况，请安装它推荐的版本。

## 配置文本编辑器或 IDE

你可以使用任意文本编辑器或集成开发环境 (IDE)，并结合 Flutter 的命令行工具，来使用 Flutter 构建应用程序。

使用带有 Flutter 扩展或插件的 IDE 会提供代码自动补全、语法高亮、widget 编写辅助、调试以及其他功能。

以下是热门的扩展插件：

- [Visual Studio Code](https://code.visualstudio.com/docs/setup/mac) 1.77 或更高版本使用 [Flutter extension for VS Code](https://marketplace.visualstudio.com/items?itemName=Dart-Code.flutter)。
- [Android Studio](https://developer.android.com/studio/install) 2023.1 (Hedgehog) 或更高版本使用 [Flutter plugin for IntelliJ](https://plugins.jetbrains.com/plugin/9212-flutter).
- [IntelliJ IDEA](https://www.jetbrains.com/help/idea/installation-guide.html) 2023.1 或更高版本使用 [Flutter plugin for IntelliJ](https://plugins.jetbrains.com/plugin/9212-flutter).

*bolt*

Flutter 团队推荐安装 [Visual Studio Code](https://code.visualstudio.com/docs/setup/mac) 1.77 或更高版本并搭配 [Flutter extension for VS Code](https://marketplace.visualstudio.com/items?itemName=Dart-Code.flutter)。这样搭配可以简化 Flutter SDK 的安装。

## 安装flutter之前

首先安装android studio，配置环境

![image-20240403003358887](C:\Users\YZQ\AppData\Roaming\Typora\typora-user-images\image-20240403003358887.png)

下载安装这两个，可能需要配置代理

![image-20240403003510934](C:\Users\YZQ\AppData\Roaming\Typora\typora-user-images\image-20240403003510934.png)

退出android studio，打开vscode，命令行用bash，并进行代理测试：

```
ping google.com
```

要求：能够稳定ping通，ping不通可以打开clash的TUN MODE

## 安装 Flutter SDK

你可以使用 VS Code Flutter 扩展或自行下载安装 Flutter 压缩包，来安装 Flutter SDK。

- [使用 VS Code 安装](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#vscode)
- [自行下载安装](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#download)

### 使用 VS Code 安装 Flutter

在使用以下流程来安装 Flutter 前，请确保你已经安装 [Visual Studio Code](https://code.visualstudio.com/docs/setup/mac) 1.77 或更高版本，以及 [Flutter extension for VS Code](https://marketplace.visualstudio.com/items?itemName=Dart-Code.flutter)。

#### 根据 VS Code 的提示，安装 Flutter

1. 启动 VS Code。

2. 打开 **命令面板 (Command Palette)**，按下快捷键 Control + Shift + P。

3. 在 **命令面板 (Command Palette)** 中输入 `flutter`。

4. 选择 **Flutter: New Project**。

5. VS Code 会提示你在计算机上找到 Flutter SDK。

   1. 如果你已经安装 Flutter SDK，请单击 **Locate SDK**。

   2. 如果你没有安装 Flutter SDK, 请单击 **Download SDK**。

      如果你没有按照 [开发工具的必要条件](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#development-tools) 安装 Git for Windows ，单击该按钮后会导航至 Flutter 安装页面。

6. 当提示 **Which Flutter template?** 的时候，请忽略它。可以按下 Esc。你可以在检查完开发配置后创建初始测试项目。

#### 下载 Flutter SDK

1. 当对话框 **Select Folder for Flutter SDK** 显示时，选择你想要安装 Flutter 的位置。

   VS Code 会打开你默认的位置。你可以选择其他位置。

   请考虑 `%USERPROFILE%` 或 `C:\dev` 这样的位置。

   *warning* **请注意：**

   不要将 Flutter 安装到以下情况的目录或路径中：

   - 路径包含特殊字符或空格。
   - 路径需要较高的权限。

   例如，`C:\Program Files` 路径就是以上情况。

2. 单击 **Clone Flutter**。

   在下载 Flutter 时，VS Code 会弹出该通知：

   *content_copy*

   ```
   Downloading the Flutter SDK. This may take a few minutes.
   ```

   下载需要一些时间。如果你怀疑下载被挂起，请单击 **Cancel** 取消下载后，再重新尝试安装。

3. Flutter 一旦完成下载， **输出 (Output)** 面板就会显示。

   *content_copy*

   ```
   Checking Dart SDK version...
   Downloading Dart SDK from the Flutter engine ...
   Expanding downloaded archive...
   ```

   成功后，VS Code 会弹出该通知：

   *content_copy*

   ```
   Initializing the Flutter SDK. This may take a few minutes.
   ```

   初始化时，**输出 (Output)** 面板会显示下面的内容：

   *content_copy*

   ```
   Building flutter tool...
   Running pub upgrade...
   Resolving dependencies...
   Got dependencies.
   Downloading Material fonts...
   Downloading Gradle Wrapper...
   Downloading package sky_engine...
   Downloading flutter_patched_sdk tools...
   Downloading flutter_patched_sdk_product tools...
   Downloading windows-x64 tools...
   Downloading windows-x64/font-subset tools...
   ```

   该进程还会运行 `flutter doctor -v`。此时，*请忽略该输出*。因为 Flutter Doctor 可能会显示与本次快速启动无关的错误。

   Flutter 安装成功后，VS Code 会弹出该通知：

   *content_copy*

   ```
   Do you want to add the Flutter SDK to PATH so it's accessible
   in external terminals?
   ```

4. 单击 **Add SDK to PATH**。

   成功后会显示通知：

   *content_copy*

   ```
   The Flutter SDK was added to your PATH
   ```

5. VS Code 可能会显示一则 Google Analytics 的通知。

   如果你同意，请单击 **OK**。

6. 在所有 PowerShell 窗口中启用 `flutter`：

   1. 关闭，然后重新打开所有 PowerShell 窗口。
   2. 重新启动 VS Code。

如果你已经安装了所有必要条件和 Flutter SDK，你应该就可以在 Windows 上为开发 Flutter。

## 配置 Android 开发

### 在 Android Studio 中配置 Android toolchain

[help帮助](https://flutter.cn/docs/get-started/install/help#android-setup)

- [首次使用 Android Studio](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#first-start)
- [正在使用 Android Studio](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#later-start)

1. 启动 **Android Studio**。

   显示 **Welcome to Android Studio** 的对话框。

2. 按照 **Android Studio Setup Wizard** 操作。

3. 安装以下组件：

   - **Android SDK Platform, API 34.0.0**
   - **Android SDK Command-line Tools**
   - **Android SDK Build-Tools**
   - **Android SDK Platform-Tools**
   - **Android Emulator**

### 配置目标 Android 设备

- [虚拟设备](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#virtual)
- [真机设备](https://flutter.cn/docs/get-started/install/windows/mobile?tab=physical#physical)

#### 配置目标 Android 设备

[help帮助](https://flutter.cn/docs/get-started/install/help#android-setup)

你需要一台运行 Android API level 21 或更高版本的安卓设备，来配置 Flutter 应用在真机 Android 设备上运行。

1. 按照 [Android 文档](https://developer.android.google.cn/studio/debug/dev-options) 中的说明，在设备上启用 **开发者选项** 和 **USB 调试**。

2. [可选] 如果要利用无线调试，请按照 [Android 文档](https://developer.android.google.cn/studio/run/device#wireless) 中的说明在设备上启用 **无线调试**。

3. 安装 [Google USB Driver](https://developer.android.google.cn/studio/run/win-usb)。

4. **这里荣耀手机（magicOS8.0）有一个很坑的地方，需要在usb选项里设置为音频来源**![image-20240403003954022](C:\Users\YZQ\AppData\Roaming\Typora\typora-user-images\image-20240403003954022.png)

5. 将设备插入你的 Windows 电脑。如果设备发出提示，请授权电脑访问你的设备。

6. 检查 Flutter 是否能识别连接的 Android 设备。

   在 PowerShell 中运行：

   *content_copy*

   ```
   c:\> flutter devices
   ```

   默认情况下，Flutter 使用 `adb` 工具所在的 Android SDK 版本。如果要在 Flutter 中使用不同的 Android SDK 安装路径，请设置环境变量 `ANDROID_SDK_ROOT` 为该安装目录。

### 同意 Android 许可证

[help帮助](https://flutter.cn/docs/get-started/install/help#android-setup)

在使用 Flutter 之前，按照指南安装所有必要的条件之后，再同意 Android SDK 平台的许可证。

1. 打开一个高权限（管理员）的控制台窗口。

2. 运行以下指令启用签名许可证。

   *content_copy*

   ```
   $ flutter doctor --android-licenses
   ```

   如果你在其他时候已经同意了 Android Studio 许可证，该指令将会返回：

   *content_copy*

   ```
   [========================================] 100% Computing updates...
   All SDK package licenses accepted.
   ```

   你可以跳过下一个步骤。

3. 请仔细阅读每项许可条款后，再同意。

#### 许可证问题故障排除

<details style="box-sizing: border-box; color: rgb(33, 33, 33); font-family: -apple-system, &quot;Google Sans&quot;, &quot;Noto Sans SC&quot;, &quot;Helvetica Neue&quot;, Helvetica, Arial, &quot;Liberation Sans&quot;, &quot;PingFang SC&quot;, &quot;Hiragino Sans GB&quot;, &quot;Source Han Sans SC&quot;, &quot;Source Han Sans CN&quot;, &quot;Microsoft YaHei&quot;, &quot;Wenquanyi Micro Hei&quot;, &quot;WenQuanYi Zen Hei&quot;, &quot;ST Heiti&quot;, SimHei, &quot;WenQuanYi Zen Hei Sharp&quot;, sans-serif; font-size: 16px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: left; text-indent: 0px; text-transform: none; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; white-space: normal; background-color: rgb(255, 255, 255); text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary style="box-sizing: border-box; display: list-item; cursor: pointer; margin-bottom: 1rem;">如何解决查找 Java 安装错误的问题</summary><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"></p><div class="language-terminal highlighter-rouge" style="box-sizing: border-box; margin-bottom: 1rem;"><div class="highlight" style="box-sizing: border-box; background: rgb(33, 33, 33); color: rgb(100, 221, 23);"><div class="code-excerpt__code" style="box-sizing: border-box; margin-bottom: 1rem; position: relative;"><button class="code-excerpt__copy-btn" type="button" data-toggle="tooltip" title="" data-clipboard-target="#code-excerpt-10" data-original-title="Copy code" style="box-sizing: border-box; border-radius: 0px; margin: 0.5rem 0px 0px; font-family: inherit; font-size: inherit; line-height: inherit; overflow: visible; text-transform: none; appearance: button; background: rgba(0, 0, 0, 0); border: none; cursor: pointer; color: rgb(84, 84, 84); position: absolute; right: 0px; outline: none !important;"><i class="material-symbols" style="box-sizing: border-box; font-family: &quot;Material Symbols Outlined&quot;; font-variation-settings: &quot;FILL&quot; 0, &quot;wght&quot; 400, &quot;GRAD&quot; 0, &quot;opsz&quot; 24; font-weight: normal; font-style: normal; font-size: 24px; line-height: 1; letter-spacing: normal; text-transform: none; display: inline-block; vertical-align: middle; white-space: nowrap; overflow-wrap: normal; direction: ltr; font-feature-settings: &quot;liga&quot;; -webkit-font-smoothing: antialiased;"></i></button><div id="code-excerpt-10" style="box-sizing: border-box;"><pre class="highlight" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; margin-top: 0px; margin-bottom: 0px; overflow: auto; display: block; color: rgb(100, 221, 23); background: rgb(33, 33, 33); padding: 0.75rem 1rem; border: 1px solid rgb(222, 226, 230);"><code style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: inherit; color: inherit; overflow-wrap: break-word; word-break: normal;"><span class="gp" style="box-sizing: border-box; user-select: none; color: rgb(255, 242, 117);"></span><span class="w" style="box-sizing: border-box;"></span><span class="nt" style="box-sizing: border-box; color: rgb(184, 234, 254);"></span><span class="go" style="box-sizing: border-box; color: rgb(255, 255, 255);"></span><span class="gp" style="box-sizing: border-box; user-select: none; color: rgb(255, 242, 117);"></span><span class="k" style="box-sizing: border-box; color: rgb(184, 234, 254);"></span></code></pre></div></div></div></div><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><strong style="box-sizing: border-box; font-weight: bolder;"></strong></p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code></p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"></p><div class="language-conf highlighter-rouge" style="box-sizing: border-box; margin-bottom: 1rem;"><div class="highlight" style="box-sizing: border-box;"><div class="code-excerpt__code" style="box-sizing: border-box; margin-bottom: 1rem; position: relative;"><button class="code-excerpt__copy-btn" type="button" data-toggle="tooltip" title="" data-clipboard-target="#code-excerpt-11" data-original-title="Copy code" style="box-sizing: border-box; border-radius: 0px; margin: 0.5rem 0px 0px; font-family: inherit; font-size: inherit; line-height: inherit; overflow: visible; text-transform: none; appearance: button; background: rgba(0, 0, 0, 0); border: none; cursor: pointer; color: rgb(84, 84, 84); position: absolute; right: 0px; outline: none !important;"><i class="material-symbols" style="box-sizing: border-box; font-family: &quot;Material Symbols Outlined&quot;; font-variation-settings: &quot;FILL&quot; 0, &quot;wght&quot; 400, &quot;GRAD&quot; 0, &quot;opsz&quot; 24; font-weight: normal; font-style: normal; font-size: 24px; line-height: 1; letter-spacing: normal; text-transform: none; display: inline-block; vertical-align: middle; white-space: nowrap; overflow-wrap: normal; direction: ltr; font-feature-settings: &quot;liga&quot;; -webkit-font-smoothing: antialiased;"></i></button><div id="code-excerpt-11" style="box-sizing: border-box;"><pre class="highlight" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; margin-top: 0px; margin-bottom: 0px; overflow: auto; display: block; color: rgb(33, 37, 41); background-color: rgb(248, 249, 250); padding: 0.75rem 1rem; border: 1px solid rgb(222, 226, 230);"><code style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: inherit; color: inherit; overflow-wrap: break-word; word-break: normal;"><span class="n" style="box-sizing: border-box; color: rgb(102, 0, 102);"></span><span class="n" style="box-sizing: border-box; color: rgb(102, 0, 102);"></span><span class="s2" style="box-sizing: border-box; color: rgb(5, 83, 177);"></span></code></pre></div></div></div></div><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"></p><div class="language-conf highlighter-rouge" style="box-sizing: border-box; margin-bottom: 1rem;"><div class="highlight" style="box-sizing: border-box;"><div class="code-excerpt__code" style="box-sizing: border-box; margin-bottom: 1rem; position: relative;"><button class="code-excerpt__copy-btn" type="button" data-toggle="tooltip" title="" data-clipboard-target="#code-excerpt-12" data-original-title="Copy code" style="box-sizing: border-box; border-radius: 0px; margin: 0.5rem 0px 0px; font-family: inherit; font-size: inherit; line-height: inherit; overflow: visible; text-transform: none; appearance: button; background: rgba(0, 0, 0, 0); border: none; cursor: pointer; color: rgb(84, 84, 84); position: absolute; right: 0px; outline: none !important;"><i class="material-symbols" style="box-sizing: border-box; font-family: &quot;Material Symbols Outlined&quot;; font-variation-settings: &quot;FILL&quot; 0, &quot;wght&quot; 400, &quot;GRAD&quot; 0, &quot;opsz&quot; 24; font-weight: normal; font-style: normal; font-size: 24px; line-height: 1; letter-spacing: normal; text-transform: none; display: inline-block; vertical-align: middle; white-space: nowrap; overflow-wrap: normal; direction: ltr; font-feature-settings: &quot;liga&quot;; -webkit-font-smoothing: antialiased;"></i></button><div id="code-excerpt-12" style="box-sizing: border-box;"><pre class="highlight" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; margin-top: 0px; margin-bottom: 0px; overflow: auto; display: block; color: rgb(33, 37, 41); background-color: rgb(248, 249, 250); padding: 0.75rem 1rem; border: 1px solid rgb(222, 226, 230);"><code style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: inherit; color: inherit; overflow-wrap: break-word; word-break: normal;"><span class="n" style="box-sizing: border-box; color: rgb(102, 0, 102);"></span><span class="n" style="box-sizing: border-box; color: rgb(102, 0, 102);"></span><span class="s2" style="box-sizing: border-box; color: rgb(5, 83, 177);"></span></code></pre></div></div></div></div><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code></p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 1rem;"><code class="language-plaintext highlighter-rouge" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; color: rgb(17, 121, 109); overflow-wrap: break-word;"></code></p><div class="language-terminal highlighter-rouge" style="box-sizing: border-box; margin-bottom: 1rem;"><div class="highlight" style="box-sizing: border-box; background: rgb(33, 33, 33); color: rgb(100, 221, 23);"><div class="code-excerpt__code" style="box-sizing: border-box; margin-bottom: 1rem; position: relative;"><button class="code-excerpt__copy-btn" type="button" data-toggle="tooltip" title="" data-clipboard-target="#code-excerpt-13" data-original-title="Copy code" style="box-sizing: border-box; border-radius: 0px; margin: 0.5rem 0px 0px; font-family: inherit; font-size: inherit; line-height: inherit; overflow: visible; text-transform: none; appearance: button; background: rgba(0, 0, 0, 0); border: none; cursor: pointer; color: rgb(84, 84, 84); position: absolute; right: 0px; outline: none !important;"><i class="material-symbols" style="box-sizing: border-box; font-family: &quot;Material Symbols Outlined&quot;; font-variation-settings: &quot;FILL&quot; 0, &quot;wght&quot; 400, &quot;GRAD&quot; 0, &quot;opsz&quot; 24; font-weight: normal; font-style: normal; font-size: 24px; line-height: 1; letter-spacing: normal; text-transform: none; display: inline-block; vertical-align: middle; white-space: nowrap; overflow-wrap: normal; direction: ltr; font-feature-settings: &quot;liga&quot;; -webkit-font-smoothing: antialiased;"></i></button><div id="code-excerpt-13" style="box-sizing: border-box;"><pre class="highlight" style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: 14px; margin-top: 0px; margin-bottom: 0px; overflow: auto; display: block; color: rgb(100, 221, 23); background: rgb(33, 33, 33); padding: 0.75rem 1rem; border: 1px solid rgb(222, 226, 230);"><code style="box-sizing: border-box; font-family: &quot;Google Sans Mono&quot;, &quot;Roboto Mono&quot;, monospace; font-size: inherit; color: inherit; overflow-wrap: break-word; word-break: normal;"><span class="go" style="box-sizing: border-box; color: rgb(255, 255, 255);"></span></code></pre></div></div></div></div></details>

## 检查你的开发配置

[help帮助](https://flutter.cn/docs/get-started/install/help)

### 运行 Flutter doctor

`flutter doctor` 指令将检查 Windows 完整的 Flutter 开发环境的所有组件。

1. 打开 PowerShell。

2. 要检查所有组件的安装情况，请运行以下指令。

   *content_copy*

   ```
   C:\> flutter doctor
   ```

由于你选择为 mobile 进行开发，因此不需要 **所有** 组件。如果你遵循本指南，指令结果应该类似于：

*content_copy*

```
Running flutter doctor...
Doctor summary (to see all details, run flutter doctor -v):
[✓] Flutter (Channel stable, 3.19.0, on Windows A.B chipset, locale en)
[✓] Windows version (Installed version of Windows is version 10 or higher)
[✓] Android toolchain - develop for Android devices (Android SDK version 34.0.0)
[!] Chrome - develop for the web
[!] Visual Studio - develop Windows apps
[✓] Android Studio (version 2023.1 (Hedgehog) or later)
[✓] VS Code (version 1.86)
[✓] Connected device (1 available)
[✓] Network resources

! Doctor found issues in 2 categories.
```

### 解决 Flutter doctor 的问题

当 `flutter doctor` 指令返回错误时，可能是 Flutter、VS Code、Android Studio、连接的设备或者网络资源出错。

如果 `flutter doctor` 指令返回这些组件中的任何一个错误，请使用 verbose 标志再次运行。

*content_copy*

```
C:\> flutter doctor -v
```

查看输出结果，了解可能需要安装的其他软件或者需要执行的其他任务。

如果你更改了 Flutter SDK 或其他相关组件的配置，请再次运行 `flutter doctor` 来检查安装。

## 管理 Flutter SDK

想要了解管理 Flutter SDK 安装的更多信息，请查阅以下内容。

- [升级 Flutter](https://flutter.cn/docs/release/upgrade)
- [卸载 Flutter](https://flutter.cn/docs/get-started/uninstall?tab=windows)



## 工程编译

创建好新工程后，编译还有坑

### 一个是编译提示：

```
exception in thread "main" java.util.zip.ZipException: zip end header not found, new version kotlin
```

解决链接：

```
https://www.youtube.com/watch?v=JFRSym81h9c
```

问题原因：

C:\Users\YZQ\.gradle    里的文件损坏导致的

解决方法：删除该文件夹

但是删除后还有坑：

### Flutter 卡在 "Running Gradle task 'assembleDebug'... "

[七厘在炼数](https://juejin.cn/user/4300945220973128/posts)

2022-04-308,910阅读1分钟

> 记得好久之前，每次Flutter增加package后，运行debug，都要在“Running Gradle task ‘assembleDebug’”卡一阵

如何解决，网上大多数都提到更换maven源。

而有时实际情况是即使你换了，还是一个niaoyang。

直到发现了这篇文章： [Flutter App stuck at "Running Gradle task 'assembleDebug'... "](https://link.juejin.cn/?target=https%3A%2F%2Fnewbedev.com%2Fflutter-app-stuck-at-running-gradle-task-assembledebug)

处理方法如下:

```less
less复制代码1.  Open your flutter Project directory.
2.  Change directory to android directory in your flutter project directory `cd android`
3.  clean gradle `./gradlew clean`
4.  Build gradle `./gradlew build` or you can combine both commands with just `./gradlew clean build` (Thanks @daniel for the tip)
5.  Now run your flutter project. If you use vscode, press F5. First time gradle running assembleDebug will take time.
```

执行`gradlew clean`后，会有下载jar的日志输出（下载了多少/jar多大）直观明了。

### Flutter App stuck at "Running Gradle task 'assembleDebug'... "

Here is solution in my case.

1. Open your flutter Project directory.
2. Change directory to android directory in your flutter project directory `cd android`
3. clean gradle `./gradlew clean`
4. Build gradle `./gradlew build` or you can combine both commands with just `./gradlew clean build`
5. Now run your flutter project. If you use vscode, press F5. First time gradle running assembleDebug will take time.

PS: Delete gradle in case of all that steps don't work



`flutter run -v` showed that I was stuck on

```
Downloading https://services.gradle.org/distributions/gradle-5.6.2-all.zip
```

使用腾讯镜像站加速：

```
https://mirrors.cloud.tencent.com/gradle/
```

This was going to take hours, as for some reason the download speed was ~10kB/s on a decent DSL connection.

Solution:

1. Interrupt gradle build
2. Download the required gradle zip from a fast mirror. e.g. https://distfiles.macports.org/gradle/gradle-5.6.2-all.zip
3. Copy `gradle-5.6.2-all.zip` to `C:\Users\ <MyUsername>\.gradle\wrapper\dists\gradle-5.6.2-all\9st6wgf78h16so49nn74lgtbb` (of course the last folder will have a different name on your PC)
4. `flutter run` and voilà.



In my case, Windows Firewall was causing this problem. After I disabled it temporarily the problem was gone. Worth giving it a try. Good luck!



If you are on Windows: try adding firewall exceptions to your Android Studio.

1. Go to:

   > Control Panel\System and Security\Windows Defender Firewall\Allowed apps

2. Hit the button:

   > Allow another app

3. Add your new firewall exceptions:

   > studio.exe and studio64.exe

## 总结

网络问题、手机问题导致大量问题

网络问题（上代理）一次不成功多试几次就行

# 发布

### 构建一个 APK

[#](https://docs.flutter.cn/deployment/android#build-an-apk)

虽然 app bundle 比 APKs 更被推荐使用，但是有一些 Store 目前还不支持 app bundle方式。这种情况下，要为各种目标 ABI (Application Binary Interface) 分别构建发布的 APK 文件。

如果你完成签名步骤，APK 就被签名了。这时你也许想要 [混淆你的 Dart 代码](https://docs.flutter.cn/deployment/obfuscate) 以加大反编译难度。混淆你的代码需要在构建时添加一些参数。

使用如下命令：

1. 输入命令 `cd [project]`。

2. Run `flutter build apk --split-per-abi`.

   运行 `flutter build apk --split-per-abi`
   （`flutter build` 默认带有 `--release` 参数。）

   `flutter build apk --split-per-abi` 命令可以生成针对不同 ABI（Application Binary Interface，应用二进制接口）的多个 APK，这主要用于优化安装包的大小，让每个 APK 只包含特定 CPU 架构（如 arm64-v8a, armeabi-v7a, x86）的支持库，从而减少每个 APK 的体积。

# 遇到的问题

## window ble

有的包在windows平台下面使用时会编译出一个Visual Studio 工程，然后通过Visual Studio 生成一些东西，但是有时候Visual Studio 版本不匹配就会有很多问题，注意报错。

## Flutter windows build: Nuget is not installed

使用一下安装：

```
winget install Microsoft.NuGet
```

