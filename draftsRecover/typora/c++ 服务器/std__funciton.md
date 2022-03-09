```c++
#include <iostream>

int add_1(int a, int b)
{
    return a+b;
}

int (*add_4)(int, int) = add_1;

auto add_2 = [](int a, int b)->int{ return a+b; };

class add_3
{
public:
    int operator()(int a, int b){
        return a+b;
    }
};


int main(int argc, char* argv[])
{
    
    int a = 1;
    int b = 2;
    fflush(stdin);
    add_3 add_5;
    std::cout << add_1(a, b);
    std::cout << add_2(a, b);
    std::cout << add_5(a, b);
    std::cout << add_4(a, b);
    return 0;
}
```
- 以上包含了普通函数，lamuda函数，函数指针，仿函数，std::function可以帮助我们将上述类型包装起来。
- std::function 是一个可调用对象包装器，是一个类模板，可以容纳除了类成员函数指针之外的所有可调用对象，它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟它们的执行。
定义格式：std::function<函数类型>。
- std::function可以取代函数指针的作用，因为它可以延迟函数的执行，特别适合作为回调函数使用。它比普通函数指针更加的灵活和便利。
- std::bind 将可调用对象与其参数一起进行绑定，绑定后的结果可以用 std::function 保存，
- std::bind的主要作用:
	- 将可调用对象何其参数绑定成一个仿函数
	- 只绑定部分参数，减少可调用对象传入的参数。
```c++
double callableFunc (double x, double y) {return x/y;}
auto NewCallable = std::bind (callableFunc, std::placeholders::_1,2);  
std::cout << NewCallable (10) << '\n';
```
- bind的第一个参数是函数名，普通函数做实参时，会隐式转换成函数指针。因此std::bind(callableFunc,_1,2)等价于std::bind (&callableFunc,_1,2)；
- _1表示占位符，位于<functional>中，std::placeholders::_1；
- 第一个参数被占位符占用，表示这个参数以调用时传入的参数为准，在这里调用NewCallable时，给它传入了10，其实就想到于调用callableFunc(10,2);


