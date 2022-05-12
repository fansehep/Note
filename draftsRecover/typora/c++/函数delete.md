## function = delete

```c++
class Base
{
 public:
 private:
    // 将函数delete掉，用的话，编译器会报错
    void dad() = delete;
};
```