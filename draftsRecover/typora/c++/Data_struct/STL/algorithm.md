# algorithm
- 1.for_each
```c++
	for_each(iterator p1, iterator p2, function);
```
	    for_each函数传入2个迭代器，表示范围，最后一个传入一个函数指针
	  会将传入两个迭代器之间的范围依次进行function操作
		
- 2.find
```c++
	find(iterator p1, iterator p2, typename val);
```
	   find会在两个迭代器之间依次进行查找，但该类必须重载==，如果没有匹
	 配成功会返回第二个迭代器的值，反之返回匹配成功那个迭代器的值
* 3.equal
```c++
	equal(iterator p1,iterator p2 ,iterator s1);
```
	equal函数用来比较两个序列是否保存相同的值，但第二个序列的size一定
	要大于前两个迭代器的大小
-  4.fill
```
	fill(iterator p1,iterator p2, typename val);
```
	fill函数会将两个迭代器之间的所有值都初始化为val；
- 5. copy
```c++
	copy(iterator p1,iterator p2, iterator s3);
```
	  copy函数接受三个迭代器，p1,p2,s3,copy函数会将前两个迭代器之间
的值依次拷贝到s3之间。
- 6unique
```c++
	unique(iterator s1, iterator s2);
```
	  unique会对顺序容器将重复元素排到后方去，返回一个迭代器，
- 7. sort
```
	sort()：
```
      sort函数有2个版本，默认情况下调用类中的比较符号，没有可以自己重载
	  但如果第三个函数，在类中实现的话，前面需要加上static
- 8. bind
```c++
	bind(function name,func arg,...);
```
	bind函数接受一个函数地址，和该函数所需要的参数，可以简单调用。
* 9.