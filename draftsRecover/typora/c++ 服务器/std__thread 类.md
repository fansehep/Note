

<font color = blue> <font color = black>
1. 默认构造函数，创建一个空的thread执行对象。
2. 初始化构造函数，创建一个thread对象，该thread对象可被joinable，新产生的线程会调用 fn 函数。
3. 拷贝构造函数已经被禁用。<font color = red>thread不可被拷贝<font color = black>
4.构造的时候传入函数直接开始运行。

```c++
// 创建一个线程
std::thread thread_1 = new std::thread();
//!! thread 构造函数
返回值 function_name(arg_1, arg_2, arg_3 );
std::thread thread_2 = new std::thread(functionname,arg_1,arg_2);
// 获取当前线程 ID
std::thread::id main_thread_id = std::this_thread::get_id();
// 睡眠当前线程
std::this_thread::sleep_for(std::chrono::seconds(n));
/* 交换两个线程的两个内部状态
	这个函数需要在创建这两个函数的内部状态使用
*/
std::this_thread::swap(std::thread& th_1,std::thread& th_2);
/* 事实上，c++ 线程类只是在各种类上做了一层封装，可以做到
夸平台的效果,底层都是封装了该系统的线程句柄或者其他什么的
pthread_t 
*/
std::thread ts;
auto tn_fd = ts.native_handle();
/* join 调用函数会阻塞当前线程。阻塞调用者 caller所在线程直至被join的
std::thread对象标识的线程执行结束。
*/
// 等待线程执行结束
ts.join();
// 分离线程，类似守护线程
ts.detach();
```
### 转移线程所有权
- std::move()
```c++
std::thread t1 = std::move(t2);
```
- 转移线程所有权，可以将一个线程的所有权转移到另外一个线程。