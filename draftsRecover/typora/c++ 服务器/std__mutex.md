C++中通过实例化std::mutex创建互斥量，通过调用成员函数lock()进行上锁，unlock()进行解锁。不过，不推荐实践中直接去调用成员函数，因为调用成员函数就意味着，必须记住在每个函数出口都要去调用unlock()，也包括异常的情况。C++标准库为互斥量提供了一个RAII语法的模板类std::lack_guard，其会在构造的时候提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁的互斥量总是会被正确的解锁。下面的程序清单中，展示了如何在多线程程序中，使用std::mutex构造的std::lock_guard实例，对一个列表进行访问保护。std::mutex和std::lock_guard都在<mutex>头文件中声明。
```c
std::lock_guard<std::mutex> lock(this->mtx);
```
- 一种符合RALL手法的锁，构造时上锁，析构时解锁，防止你忘记上锁。
- 但其实这是一种粒度很大的锁，一般来说，这会让你整个函数上锁。
```c
std::unique_lock<std::mutex> your_lock(this->mtx);
yourlock.lock();	// 上锁
yourlock.unlock();	// 解锁
```
- 偏小粒度锁
---
- call_once
```c++
template< class Callable, class... Args >
void call_once( std::once_flag& flag, Callable&& f, Args&&... args );
```
- 若在调用 call_once 的时刻， flag 指示已经调用了 f ，则 call_once 立即返回（称这种对 call_once 的调用为消极）。
- 否则， call_once 以参数 std::forward<Args>(args)... 调用 std::forward<Callable>(f) （如同用 std::invoke ）。不同于 std::thread 构造函数或 std::async ，不移动或复制参数，因为不需要转移它们到另一执行线程（称这种对 call_once 的调用为积极）。
- 若该调用抛异常，则传播异常给 call_once 的调用方，并且不翻转 flag ，以令其他调用将得到尝试（称这种对 call_once 的调用为异常）。
- 若该调用正常返回（称这种对 call_once 的调用为返回），则翻转 flag ，并保证以同一 flag 对 call_once 的其他调用为消极。
- 同一 flag 上的所有积极调用组成单独全序，它们由零或多个异常调用后随一个返回调用组成。该顺序中，每个积极调用的结尾同步于下个积极调用。

- 从返回调用的返回同步于同一 flag 上的所有消极调用：这表示保证所有对 call_once 的同时调用都观察到积极调用所做的任何副效应，而无需额外同步。
---
- 读写锁
```c++
boost::shared_mutex<>;
```
- 同一时间内，只有一个线程可以写，多个线程可以并行读。


