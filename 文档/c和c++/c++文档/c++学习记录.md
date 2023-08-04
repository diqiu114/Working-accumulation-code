c++经过大量的版本更替，越来越现代化，应当学习现代c++

c++相比于c多了许多特性：

## 指针

现代c++提倡使用智能指针unique_ptr，智能会自动销毁

示例：

```
class LargeObject
{
public:
    void DoSomething(){}
};

void ProcessLargeObject(const LargeObject& lo){}
void SmartPointerDemo()
{    
    // Create the object and pass it to a smart pointer
    std::unique_ptr<LargeObject> pLarge(new LargeObject());

    //Call a method on the object
    pLarge->DoSomething();

    // Pass a reference to a method.
    ProcessLargeObject(*pLarge);

} //pLarge is deleted automatically when function block goes out of scope.
```

在能够精准把控的小模块中和要求高性能的地方使用原始指针

```
void UseRawPointer()
{
    // Using a raw pointer -- not recommended.
    Song* pSong = new Song(L"Nothing on You", L"Bruno Mars"); 

    // Use pSong...

    // Don't forget to delete!
    delete pSong;   
}
```



## 访问全局内容

```
#include <iostream>

int i = 7;   // i has global scope, outside all blocks
using namespace std;

int main( int argc, char *argv[] ) {
   int i = 5;   // i has block scope, hides i at global scope
   cout << "Block-scoped i has the value: " << i << "\n";
   // 使用“::”符号访问全局i
   cout << "Global-scoped i has the value: " << ::i << "\n";
}


```

## 新式c++错误处理的最佳方式

程序错误通常分为两种类别：

1. 由编程失误导致的逻辑错误，例如“索引超出范围”错误。
2. 以及超出程序员控制范围的运行时错误，例如“网络服务不可用”错误。

异常捕获和理解：

1. 异常通过throw抛出
2. 抛出异常处中断该函数运行，并直接逐层销毁
3. 销毁完毕运行catch内容

例子：

```
#include <string>
#include <iostream>
using namespace std;

class MyException{};
class Dummy
{
    public:
    Dummy(string s) : MyName(s) { PrintMsg("Created Dummy:"); }
    Dummy(const Dummy& other) : MyName(other.MyName){ PrintMsg("Copy created Dummy:"); }
    ~Dummy(){ PrintMsg("Destroyed Dummy:"); }
    void PrintMsg(string s) { cout << s  << MyName <<  endl; }
    string MyName;
    int level;
};

void C(Dummy d, int i)
{
    cout << "Entering FunctionC" << endl;
    d.MyName = " C";
    throw MyException();

    cout << "Exiting FunctionC" << endl;
}

void B(Dummy d, int i)
{
    cout << "Entering FunctionB" << endl;
    d.MyName = "B";
    C(d, i + 1);
    cout << "Exiting FunctionB" << endl;
}

void A(Dummy d, int i)
{
    cout << "Entering FunctionA" << endl;
    d.MyName = " A" ;
  //  Dummy* pd = new Dummy("new Dummy"); //Not exception safe!!!
    B(d, i + 1);
 //   delete pd;
    cout << "Exiting FunctionA" << endl;
}

int main()
{
    cout << "Entering main" << endl;
    try
    {
        Dummy d(" M");
        A(d,1);
    }
    catch (MyException& e)
    {
        cout << "Caught an exception of type: " << typeid(e).name() << endl;
    }

    cout << "Exiting main." << endl;
    char c;
    cin >> c;
}

/* Output:
    Entering main
    Created Dummy: M
    Copy created Dummy: M
    Entering FunctionA
    Copy created Dummy: A
    Entering FunctionB
    Copy created Dummy: B
    Entering FunctionC
    Destroyed Dummy: C
    Destroyed Dummy: B
    Destroyed Dummy: A
    Destroyed Dummy: M
    Caught an exception of type: class MyException
    Exiting main.

*/
```

其中可以在函数申明中使用noexcept关键字（C++11标准，表示该函数是否会抛出异常）

```
void func_not_throw() noexcept; // 保证不抛出异常
void func_not_throw() noexcept(true); // 和上式一个意思

void func_throw() noexcept(false); // 可能会抛出异常
void func_throw(); // 和上式一个意思，若不显示说明，默认是会抛出异常（除了析构函数，详见下面）
```

## operator关键字

通过operator可以重载运算符，如+、-、==、=等等

使用方式：

```
class OperatorTestClass
{
public:
    OperatorTestClass(int val)
    {
        this->val = val;
    }
    // 把<运算符重载为==
	bool operator<(const OperatorTestClass& arg)
	{
		cout<<"重载运算符测试"<<endl;
		return this->val == arg.val;
	}
private:
    int val;
};

int main()
{
    OperatorTestClass temp1(10);
    OperatorTestClass temp2(10);
	// 这里把temp1<看成函数，temp2看成参数，得到类似：temp.1operator(temp2)效果
    if(temp1<temp2) {
        cout << "运算符重载成功" << endl;
    }
    return 0;
}
```



## 临时对象

c++中会产生几种临时对象：

1. ```
   void Func()
   {
   	// 产生一个临时对象
   	Class_Exemple temp();
   }
   ```

2. ```
   Class_Exemple Func(Class_Exemple temp)
   {
   	// 产生一个临时对象
   	return  temp;
   }
   
   void main()
   {
   	Class_Exemple main_temp;
   	// 产生2个临时对象，main_temp作为参数传给Fun的形参temp时，会生成temp临时对象，
   	// temp返回时，会进行生成一个对象复制temp，在覆盖掉main_temp
   	main_temp = Func(main_temp);
   	return 0;
   }
   ```

   ## const关键字
   
   ## `const` 成员函数
   
   声明带 **`const`** 关键字的成员函数将指定该函数是一个“只读”函数，它不会修改为其调用该函数的对象。 常量成员函数不能修改任何非静态数据成员或调用不是常量的任何成员函数。 若要声明常量成员函数，请在参数列表的右括号后放置 **`const`** 关键字。 声明和定义中都需要 **`const`** 关键字。
   
   注解：这里就是说，const出现在函数声明后，形如这样：int getMonth() const{}，表明函数体内的东西都是不可变更的。
   
   ```cpp
   // constant_member_function.cpp
   class Date
   {
   public:
      Date( int mn, int dy, int yr );
      int getMonth() const;     // A read-only function
      void setMonth( int mn );   // A write function; can't be const
   private:
      int month;
   };
   
   int Date::getMonth() const
   {
      return month;        // Doesn't modify anything
   }
   void Date::setMonth( int mn )
   {
      month = mn;          // Modifies data member
   }
   int main()
   {
      Date MyDate( 7, 4, 1998 );
      const Date BirthDate( 1, 18, 1953 );
      MyDate.setMonth( 4 );    // Okay
      BirthDate.getMonth();    // Okay
      BirthDate.setMonth( 4 ); // C2662 Error
   }
   ```

## 引用和指针的区别

指针是用一个变量存了另一个变量的地址

引用本质上还是原变量，只是用另外一个名称进行了替代

## lamabda表达式

形如：

```
[]() {

}
```

其中[]中存放的表示捕获列表，捕获的是位于该作用域内的临时变量，他有以下形式

```
// 以值的形式捕获本作用域下所有的变量
[=]() {

}
// 以引用的形式捕获本作用域下所有的变量
[&]() {

}

int i = 10;
// 只对i的值进行捕获
[=, i]() {
	int j = i;
}
```



## 模板

形如：

```
template <typename T>
T minimum(const T& lhs, const T& rhs)
{
    return lhs < rhs ? lhs : rhs;
}
```

在编译中，编译器会推导T类型，然后再把模板中的t替换掉

### typename 

**`typename`** 向编译器提供未知标识符为类型的提示。 在模板参数列表中，它用于指定类型参数

