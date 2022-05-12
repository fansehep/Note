- 默认情况下，我们会调用read 和 write函数来开辟一块缓冲区，但这往往会带来多次的系统调用而带来不必要的性能开销。
- readv 和 writev 则很好的解决了这个问题。
```c
ssize_t readv(int fd, const struct iovec* iov, int iovcnt);
ssize_t writev(int fd, cosnt struct iovec* iov, int iovcnt);
```
---
```c
struct iovec{
	void* iov_base;
	size_t iov_len;
};
```
![](https://img-blog.csdnimg.cn/20191113114947547.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zNjc1MDYyMw==,size_16,color_FFFFFF,t_70)