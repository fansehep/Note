# Weak_ptr
- 1.weak_ptr是一种不控制所指对象周期的智能指针，他指向一个shared_ptr管理的对象，可以把一个weak_ptr绑定到一个shared_ptr上，不会改变shared_ptr的引用计数，一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放，即使有weak_ptr指向对象，对象仍然会被销毁。
- 2.支持方法
```c++
	w = p; //赋值后共享对象
	w.reset();//将w置空
	w.use_count();//与w共享对象的shared_ptr的数量
	w.expired(); //use_count()为0，返回true，不为0，返回false
	w.lock();//如果expired为true，返回一个空的shared_ptr,否则返回一个指向w的对象shared_ptr
```
- 3.当我们创建一个weak_ptr时，需要用一个shared_ptr来初始化。
- 4.