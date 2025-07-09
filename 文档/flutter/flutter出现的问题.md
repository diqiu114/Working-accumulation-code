荣耀手机在进行调试时运行

```
flutter run
```

会发现卡在了

```
Flutter: Installing build\app\outputs\flutter-apk\app-debug.apk
```

只有就没有信息了，这是不对的，应该还会打印

```
Flutter run key commands.
r Hot reload.
R Hot restart.
h List all available interactive commands.
d Detach (terminate "flutter run" but leave application running).
c Clear the screen
q Quit (terminate the application on the device).
```

等信息

再运行

```
flutter doctor -v
```

就会发现一直卡在

```
 Waiting for VM Service port to be available...
```

这个问题是荣耀手机的问题，需要关闭一下开发者模式再打开就行了

论坛上也提到了这个问题

```
https://www.reddit.com/r/Honor/comments/1g7xfha/flutter_debugging_issues_on_honor_magic_6_pro/
```

