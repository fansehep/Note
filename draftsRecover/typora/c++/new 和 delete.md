- 1. new的返回值是一个new 的后面的对象的指针，如果失败，会抛出一个异常，bad_alloc，我们可以改变使用new的方式来阻止他抛出异常。
- 2. 但同时我们每次new出来的对象，是需要我们手动去释放的，