### std::move()

- 1. c++ 默认会有拷贝构造函数，赋值拷贝函数。

  2. 我们来看一例

     ```c++
     #include <iostream>
     #include <vector>
     #include <string.h>
     
     class A
     {
     public:
       A()
       {
         printf("A constructor ...\n");
         ptr_ = new int(100);
       }
       A(const A &a)
       {
         printf("A copy constructor ...\n");
         ptr_ = new int();
         memcpy(ptr_, a.ptr_, sizeof(int));
       }
       ~A()
       {
         printf("A deconstror ...\n");
         if (ptr_)
         {
           delete ptr_;
         }
       }
       A &operator=(const A &a)
       {
         printf("A operaotr = ...\n");
         return *this;
       }
       int *getVal()
       {
         return ptr_;
       }
       A(A&& a)
       {
         printf("A move construct ...\n");
         ptr_ = a.ptr_;
         a.ptr_ = nullptr;
       }
     private:
       int *ptr_;
     };
     int main(void)
     {
     /*
     * vec.emplace_back(A());
     * A() 生成一个对象， 内部vector<> 又构造一个对象， 并调用拷贝构造函数，再次赋值。
     * A cons
     * A copy cons
     * A decon
     * A decon
     *
     * 于是，c++ 11 后引入了一种移动构造函数。
     */
       std::vector<A> vec;
       vec.push_back(std::move(A()));
       return 0;
     }
     ```

  3. 这里，我们如果不用std::move() 来进行移动拷贝函数，那么我们知道, 这样做是会有性能损失的。

  4. 我们来回忆一下左值和右值的区别

     1. 左值即可以修改，在内存之中真正存在的值。

     2. 右值，则像是 3,4 这些临时保存在寄存器中的值。

        ```c
        int a = 10;
        // a 即为左值， 10 则是右值。
        ```

  5. c++ 11 中则又引入了右值引用概念。6