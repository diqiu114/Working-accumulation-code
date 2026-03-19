Qwidget 基础窗口类：所有窗口，或者控件的父类，QApplication\QDalog都继承自它







main：

​	![image-20221216110419775](C:\Users\DACHI\AppData\Roaming\Typora\typora-user-images\image-20221216110419775.png)



表示窗口的一般都会继承自QObject  





使用对象树：（更方便内存管理）

当窗口构造为对象树的结构时，父对象在释放析构的时候，会自动释放子对象 

创建对象的方式基本上使用new来进行，







信号和槽机制：

信号：各种事件

槽：响应信号的动作







自定义信号

一些规矩：

1. 声明在类头文件的signals域下面
2. void类型的函数，没有返回值
3. 可以有参数，也可以重载
4. 只有声明，没有实现（qt在编译阶段自己添加）
5. 触发信号emit boj->sign(参数。。。)

自定义槽：

1. qt5可以声明在类的任何位置，还可以时静态成员函数、全局函数、lambda表达式
2. void类型的函数，没有返回值
3. 可以有参数，也可以重载
4. 不仅有声明，还得有实现

信号槽扩展：

1. 一个信号可以连接多个槽
   1. 一个信号建立了多个connect，当发生信号发射时，槽函数的调用顺序时随机的
2. 一个槽可以了解多个信号
3. 信号可以连接信号
   1. connect（第一个信号发送者，第一个信号，第二个信号发送者，第二个信号）
4. 信号和槽的参数关系必须满足以下两点
   1. 信号和槽函数的参数类型必须对应
   2. 信号和槽函数的参数个数不需要一致，信号函数参数个数>=槽函数参数个数
      1. hungry(QString)		->		treat()		ok
      2. hungry(QString)        ->		treat(int)    编译出错
5. QTDebug:
   1. QTDebug默认将QString转义输出
   2. 解决方法：
      1. 将QString转成char*

Lambda表达式（匿名函数对象）：

推荐使用形式`[=]() {}`

1. 

```c
int a;
int b;
// 默认传递（传递捕获）参数为const：
[a, b]()
{
    qDebug() << "hello lamabda" << Qt::endl;
    qDebug() << a * b;
};
// = 局部变量全部使用值传递捕获，捕获局部变量包括this
// & 局部变量全部使用应用传递捕获进来
// [=, b]() // 除b为捕获传递，其他都是。。。
// [&a, b]()

```

2. 需要修改值的话，传递捕获中需要&
3. 选项Opt
   1. 常用的是使用mutable声明，可以达到允许修改，值传递的拷贝效果
   2. 

Lamabda在信号和槽中的应用：

```c++
connect(pBnt, &QPushButton::clicked, [=]() {
    qDebug() << a * b << Qt::endl;
});
```

总结：信号和槽：去网上找。。。。。 





# qml

### 图形位置应用

```
import QtQuick
import QtQuick.Window
import QtQuick.Shapes
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        width: 100
        height: 100
        color: "#123212"
        x:120
        y:100
        z:101
    }
    Rectangle {
        width: 100
        height: 100
        color: "#456434"
        x:100
        y:100
        z:102
        clip: true  // 裁剪，子对象超出父对象的部分不显示
        Rectangle {
            width: 100
            height: 100
            color: "yellow"
            x:50
            y:50
            z:102
        }
    }

}
```

### 锚布局

```
import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: main
        width: 100
        height: 100
        color: "#123212"
        x:100
        y:100
        z:101
    }
    Rectangle {
        width: 100
        height: 100
        color: "#456434"
        y:100
        z:102
        anchors.right:main.left // 锚布局，此控件的右边对齐某id的左边
    }

}

```



## Shape —— 渲染容器

这种渲染器，类似矢量图的概念，矢量图的渲染都是计算出来的（贝塞尔曲线），类比qt中的渲染，也需要去描述图形绘画的公式，然后qt中还加上了分层，那么，每层就有每层负责的东西，详细如下：

`Shape` 相当于 **画布 + GPU 渲染器**。

职责：

- 管理绘制
- 提供尺寸
- 决定使用哪个 renderer
- 把路径交给 GPU 画出来

例子：

```
Shape {
    width: 200
    height: 200
}
```

它本身 **不描述形状**。

### ShapePath —— 路径样式

`ShapePath` 定义 **路径的绘制方式**：

- 填充
- 描边
- 线宽
- join / cap

例如：

```
ShapePath {
    fillColor: "green"
    strokeColor: "black"
    strokeWidth: 2
}
```

它相当于 **画笔 + 画刷**。

### PathXXX —— 路径几何

`PathRectangle`、`PathLine`、`PathArc` 等只负责：

**定义几何路径**

例如：

```
PathRectangle {
    width: 200
    height: 100
}
```

它相当于：

> “在路径里加一个矩形”。

### 示例代码

渲染+变量

```
import QtQuick
import QtQuick.Window
import QtQuick.Shapes
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Shape {
        id: rectangleShape
        width: 200
        height: 150
        anchors.centerIn: parent
        preferredRendererType: Shape.CurveRenderer
        property color rectColor: "#3ad23c"


        ShapePath {
            fillColor: rectangleShape.rectColor

            PathRectangle {
                width: rectangleShape.width
                height: rectangleShape.height
                topLeftRadius: 30
                bottomRightRadius: 30
                bevel: true
                Component.onCompleted: {
                    console.log("sdfslkdfjlsf")
                }
            }
        }
    }

    Button {
        text: "Ok"
        width: 100
        height: 100 
        onClicked: {
            rectangleShape.rectColor = "#ff00ff"
        }

    }

}
```

