## std::move and std::forward

- 移动语义 

  - 使编译器用更高效的移动操作代替昂贵的复制操作。
  - 移动语义也允许创建只可移动的类型
    -  std::unique_ptr
    - std::future
    - std::thread

- 完美转发

  - 使接受任意数量参数的函数模板成为可能。
  - 他可以讲参数转发到其他的函数，使目标函数接受到的参数与被传递给转发函数的参数保持一致。

- ```c++
  void Func(Widget&& w);
  // 牢记参数永远是左值。即使类型是一个右值引用。
  ```

- std::move() 事实上不移动任何东西。std::forward<>() 事实上也不转发任何东西。在运行期间不做任何事情，不产生任何可执行代码。一字节都没有。

  std::move() 源码

  ```c++
  template<typename T>
  typename remove_reference<T>::type&&
  move(T&& param)
  {
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);  
  }
  ```

  std::move 返回的是右值引用。

  - ```c++
    class Annotaion {
    public:
    //* 注意text 并不是被移动到value，而是被复制。
      explicit Annotaion(const std::string text) : text_(std::move(text)) {} 
    private:
      std::string text_;  
    };
    class string {
    public:
      string(const string& rhs);
      strubg(string&& ths);
    };
    ```

  - 这里text 的类型是 const std::string, 但是移动构造函数只接受普通的string, 语言上不允许将常量对象传递给可以修改他们的函数。

  - 1. 不要在移动对象的时候，声明他们为常量。对常量对象的移动请求会**悄无声息的转化为复制操作**
    2. std::move 不移动任何东西，而且也不保证它所执行的对象可被移动。

  - ```c++
    void Process(const String &a)
    {
      printf("left value\n");
    }
    void Process(String &&b)
    {
      printf("right value\n");
    }
    template <typename t>
    void logandprocess(t &&arg)
    {
      Process((arg));
    }
      logandprocess(a);
      logandprocess(std::move(a));
    ```

  - 由于我们知道函数参数永远是left_value, 所以这里永远只会调用const string& 该版本。

  - 但如果，我们在Process(std::forward<String>());改成这样。std::forward 则会自动判断出传入数据类型，当我们想要使用右值使用std::move 即可。

  - std::forward 则只将 由 右值初始化的参数转化为右值。

  

  

  

  

  

  

  