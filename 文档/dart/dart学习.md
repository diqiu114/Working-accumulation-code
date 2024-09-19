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

