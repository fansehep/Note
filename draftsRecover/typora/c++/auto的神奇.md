## auto

- auto具有类型推导的作用，在平常可以简化我们代码的书写

- 获取类型名称

  - ```c++
    #include <typeinfo>
    #include <cxxabi.h>
    
    abi::__cxa_demangle(typeid(s).name(), nullptr, nullptr, nullptr)
    // 该函数可以获取变量的类型全拼
    ```

- 坑点

  - ```c++
    auto s(1); 
    auto f{1};
    // 此时 s 和 f 都是int
    auto f = {1} 
    // f = std::initializer_list<int>
    // 暂时不清楚为什么老是要推导出
    // std::initializer
    ```
    
  - 

