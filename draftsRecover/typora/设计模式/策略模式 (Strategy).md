#### 动机 : 在软件构建过程中，某些对象使用的算法可能多种多样？经常改变，如果将这些算法都编码到对象中，将会使对象变得异常复杂；而且有时候支持不使用的算法也是一个性能负担。
- 如何在运行时根据需要透明地更改对象的算法？将对象与算法解耦,从而避免上述问题?
![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-13%2011-26-25%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
	- 此处通过多态来避免大量的 if else 判断。
	- 含有许多条件判断的情况时，一般都需要 Strategy 模式。
![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-13%2011-40-33%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

- Strategy 及其子类为组件提供了一系列可重用的算法，从而可以使得类型在运行时方便地根据需要在各个算法之间进行切换。
- Strategy 模式提供了用条件判断语句以外的另一种选择，消除条件判断语句，就是在解耦合。
- 如果 Strategy 对象没有实例变量，那么各个上下文可以共享同一个 Strategy 对象，从而节省对象开销。

