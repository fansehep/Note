# Unique_ptr
- 1.unique_ptr表示单一时刻只能有一个unique_ptr指向一个对象，当unique_ptr被销毁时，他所指向的对象也直接被销毁，
- 2.unique_ptr 可以直接用 new 关键字所返回的对象初始化，unique不支持赋值，unique也不支持拷贝
- 3.函数有如下
```c++
	u = nullptr; //直接释放u所指向的对象，将u置空
	u.release(); //u放弃对指针的控制权，返回指针，并将u
	u.reset(); //释放u指向的对象
	u.reset(q);//如果提供了内置指针,令u指向q这个对象，否则将u置空
```
- 4.调用release会切断unique_ptr和他原来管理的对象之间的关系，release所返回的指针，通常被用来初始化另外一个智能指针，或者给另外一个智能指针赋值。
```c++
	unique_ptr<int> clone(int p)
	{
		return unique_ptr<int>(new int(p));
    }
/*还可以返回局部对象的拷贝，在这两段代码里，编译器会自动优
化掉，因为函数结束会自动销毁*/
```
- 5.unique身为智能指针同样也可以重载自己的销毁函数，有一些类没有析构函数，那就要自己写咯。
- 6.
