# 语法部分

## 运算符号

### ??

在 Dart 编程语言中，`??` 被称为空合并运算符（null-coalescing operator）。它的作用是：如果左侧的表达式不为 `null`，则返回左侧的值；否则，返回右侧的值。

**用法示例：**

```
dart复制代码void main() {
  String? username;
  String displayName = username ?? '默认用户名';
  print(displayName); // 输出：默认用户名
}
```

在上述代码中，`username` 可能为 `null`。使用 `??` 运算符，可以为 `displayName` 提供一个默认值，防止出现 `null` 值导致的错误。

### as

```
class Test{
  void func()
  {
    print("object");
  }
}

void main()
{
  var test;
  test = "";
  test = Test();
  // 此时这个不可以用
  // test.func();
  // 强制类型转换
  (test as Test).func();
}
```

### ..

```
class Test{
  var num = 10;
  var name = "sdfsdf";
  void func()
  {
    print("${num}, $name");
  }
}

void main()
{
  var test = Test();
  // 练级操作
  test..num = 30..name = "zhangsan"..func();
}
```



## **Map**：

示例：

```
final Map<String, dynamic> params = <String, dynamic>
```

解释：

在Dart中，这行代码声明了一个名为 `params` 的变量，它是一个 `Map` 类型的对象，键（Key）是 `String` 类型，值（Value）是 `dynamic` 类型。

- `final`: 这表示 `params` 是一个只读的（不可变的）变量，一旦赋值后就不能再修改。
- `Map<String, dynamic>`: 这部分指定了 `params` 是一个 `Map` 类型的变量，并指定了键的类型为 `String`，值的类型为 `dynamic`。
- `= <String, dynamic>{}`: 这是一个赋值语句，将一个空的 `Map` 对象赋值给 `params` 变量。`<String, dynamic>{}` 表示一个空的 `Map`，其中 `<String, dynamic>` 是类型参数，用于指定键值对的类型。

综合起来，这行代码声明了一个只读的 `Map` 类型的变量 `params`，其键为 `String` 类型，值为 `dynamic` 类型，并将一个空的 `Map` 对象赋值给它。在后续代码中，可以使用 `params` 变量来存储和访问键值对数据，但不能修改 `params` 的引用或内容。

## dynamic

在Dart中，`dynamic` 是一种特殊的数据类型，它表示一个可以存储任意类型的值的变量。当一个变量被声明为 `dynamic` 类型，Dart 编译器将不会对其类型进行静态检查，也就是说，你可以给这个变量赋予任何类型的值，并且编译器不会报错。

使用 `dynamic` 类型可以在一些特定情况下更灵活地处理数据，但也需要注意潜在的类型错误。因为 `dynamic` 变量不受类型约束，如果在运行时给它赋值了错误的类型，可能会导致运行时错误。

比如，在使用 `dynamic` 类型时，你可以这样做：

```
dartCopy codedynamic myVariable = 42;
print(myVariable); // Output: 42

myVariable = "Hello";
print(myVariable); // Output: Hello

myVariable = [1, 2, 3];
print(myVariable); // Output: [1, 2, 3]
```

在上面的例子中，`myVariable` 是一个 `dynamic` 类型的变量，它先后存储了一个整数、一个字符串和一个列表。这样的灵活性可以在一些特定场景下派上用场，但同时也要小心潜在的类型错误，因为在编译时不会有类型检查的帮助。在大多数情况下，建议使用更具体的类型来声明变量，以便在编译时能够发现潜在的类型错误。



## 函数

### 可选参数

参数使用“[]”包括:

```
int func(int num, [int num2, int num3])
{
	return 10;
}
```

### 参数为函数：

```
void fun_print()
{
  print("hello");
}

void func(pfunc)
{
  pfunc();
}

void main()
{
  func(fun_print);
}
```

### 闭包

```
void main() {
  func(){
    var num = 10;
    return (){
      num++;
      print(num);
    };
  }
  var f = func();
  f();
  f();
  f();
}

```

作用：（闭包其实就是缩小版的类）在var f定义时，实例化产生，func函数中的num一并实例化，后续f变量都没有被释放，所以，num也没有释放，这里达到了和c里面的静态变量的作用，f释放后，num函数一并被释放。

## 类

### 构造函数

```dart

class Test{
  // 构造函数
  Test(){
    print("默认构造函数");
  }
  Test.print_info(){
    print("命名构造函数");
  }
}

void main()
{
  var test = Test.print_info();
}
```

### 变成模块

```dart
/**
 * dart的类中的私有
 * 前提：只有在单独的文件中才有效果
 */
class Test{
  // 构造函数
  Test(){
    print("默认构造函数");
  }
  Test.print_info(){
    print("命名构造函数");
  }
  void _print()
  {
      print("私有方法");
  }
}
void main()
{
  var test = Test();
  // 同一文件中还是能够使用私有方法
  test._print();
}
```

### getter和setter

相当于一个语法糖，在语法层面将本该写成函数的语句简化了，get只有返回值没有形参，set只有形参没有返回值，形如 以下：

```
class Test{
  var test_num = 10;
  // getter修饰符
  get num => test_num;
  get num2{
    return test_num;
  }
  //setter修饰符
  set set_num(var args) {
    this.test_num = args;
  }
}
void main()
{
  var test = Test();
  print(test.num);
  test.set_num = 20;
  print(test.num2);

}
```

### 初始化列表

```
class Test{
  /**初始化列表，和c++中初始化列表有点像，不同的是
   * c++的初始化列表会覆盖Test类中，比如int a = 10，后面初始化
   * 列表又初始化a，这里会被合并为一步
   * dart中是先int a = 10，再进行初始化话列表操作，是两步
   */
  int a = 10;
  Test(int num):a = 20 {
    num = 20;
    print(a);
  }
  Test.fun(){
    print(a);
  }

}
void main()
{
  var test = Test.fun();
}


```

### 静态属性和静态方法

```
class Test{
  /**静态属性和静态方法
   * 静态相当啊于c中ram里的静态区域，属于是程序启动就实例化的
   * 所以不能够访问动态分配的东西
   * 静态方法和动态方法区别就是，访问时的权限不一样而已
   * 静态方法只能通过类名直接使用，动态方法只能通过示例化类使用
   */
  static var num = 10;
  var num2 = 30;
  static void func()
  {
    print(num);
  }
  void func_2()
  {
    print(num);
  }

}
void main()
{
  Test.func();
  print(Test.num);
  var test = Test();
  // 实例化的对象访问不了静态方法
  test.func_2();
}


```

### 继承

#### super

给父类构造函数传参

```
class Test{
  var num = 10;
  var name = "sdfsdf";
  void func()
  {
    print("${num}, $name");
  }
  Test(var num, var name)
  {
    this.num = num;
    this.name = name;
  }
}

class Test2 extends Test{
  Test2(super.num, super.name);
  // Test2(var num, var name):super(num, name);
}

void main()
{
  var test = Test2(10, "ceshi");
  test.func();
}


```

#### override，以及override调用父类方法

```dart
class Test{
  var num = 10;
  var name = "sdfsdf";
  void func()
  {
    print("${num}, $name");
  }
  Test(var num, var name)
  {
    this.num = num;
    this.name = name;
  }
}

class Test2 extends Test{
  Test2(super.num, super.name);
  // Test2(var num, var name):super(num, name);
  @override // 加上这个标签，更明确的表示这是一个复写，可以不加
  void func(){
    print("sub");
    // 使用super调用父类方法
    super.func();
  }
}

void main()
{
  var test = Test2(10, "ceshi");
  test.func();
}
```

### 多态（抽象类）

```
// 抽象类约束子类必须要实现抽象类中的方法，相当于c++中的虚函数
abstract class Test1{
  fuc(var num, var name);
  void print_() {
    print("普通方法");
  }
}

class Test2 extends Test1{
  @override
  fuc(num, name) {
    print("$num, $name");
  }


}


void main()
{
  var test = Test2();
  test.fuc(10, "sdf");
  var test2 = Test2();
  test2.fuc("30", 90);
  test2.print_();
}
```

### 接口

使用implements关键词对抽象类进行实现，implements表示子类必须实现父类所有方法

```
abstract class Test1{
  fuc1(var num, var name);
  void print_() {
    print("普通方法");
  }
}

class Test2{
  fuc()
  {
    print("Test2");
  }
}
// 必须实现所有父类的所有函数
class Test3 implements Test1, Test2{
  @override
  fuc() {
    // TODO: implement fuc
    throw UnimplementedError();
  }

  @override
  fuc1(num, name) {
    // TODO: implement fuc1
    throw UnimplementedError();
  }

  @override
  void print_() {
    // TODO: implement print_
  }

}

void main()
{
  var test = Test3();
  
}
```

### 多继承



## 名词解释

### 依赖注入库

依赖注入的核心思想是将一个对象所依赖的其他对象（即依赖）传递给它，而不是让它自己去创建这些依赖。这样可以避免类之间紧耦合，提升代码的灵活性。

```
class Engine {
  void start() {
    print('Engine started');
  }
}

class Car {
  final Engine engine;

  // 通过构造函数注入依赖
  Car(this.engine);
  /* 这里相当于：
  	Car(Engine engine)
  	{
  		this.engine = engine;
  	}
  */

  void drive() {
    engine.start();
    print('Car is driving');
  }
}

void main() {
  Engine engine = Engine();
  Car car = Car(engine);
  car.drive();
}

```

