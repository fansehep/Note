# 1.关闭连接
```c++
	int close( int fd );
```
- close的调用并非总是立即关闭一个连接，而是将fd的引用计数减去1，只有当fd的引用计数为0时，才真正关闭连接。多进程程序中， fork之后的，会将父进程中所有的socket引用计数加一，当我们需要关闭连接时，必须关闭父子进程中的socket。
```c++
	int shutdown( int sockfd, int howto );
```
- 但我们无论何时都要立即终止连接时，可以调用shutdown函数
```c++
// howto的可选项 
SHUT_RD		关闭读选项
SHUT_WR		关闭写选项
SHUT_RDWR	SHUT_RD && SHUT_RDWR
```
# 2. The API for TCP / UDP
- ## TCP
```c++
ssize_t recv(int sockfd,void* buf,size_t buf,int flags);
ssize_t send(int sockfd,const void* buf,size_t len,int flags);
```
- 函数具体就不介绍了
```
看flags函数的参数
详情请见 本书高性能 P82
```
- ## UDP
```c++
ssize_t recvfrom(int sockfd,void* buf,size_t len,int flags,struct sockaddr* src_addr,socklen_t* addrlen);
ssize_t sendto(int sockfd,const void* buf,size_t len,int flags,const struct sockaddr* dest_addr,socklen_t addrlen );
```
- 由于UDP是无状态连接，所以他的每次发送消息和接受消息都必须指定端口号和属性。
- 当然这个函数其实也可以用于TCO stream的连接，只需要把最后两个参数设为NULL即可
## 3.通用的数据读写函数
```c++
ssize_t recvmsg(int sockfd,struct msghdr* msg,int flags);
ssize_t sendmsg(int sockfd,struct msghdr* msg,int flags);
```
- 这些函数不仅能用于TCP流数据，还可用于UDP数据报。
```c++
struct msghdr
{
	void* msg_name;		//socket 地址
	socklen_t msg_namelen;	//socket地址长度
	struct iovec* msg_iov;	//分散的内存块
	int msg_iovlen;		//分散的内存块的数量
	void* msg_control;		//指向辅助数据的起始位置
	socklen_t msg_controllen;	//辅助数据的大小
	int msg_flags;		//赋值函数的flags参数，并在调用过程中更新
}
```
- msg_name成员指向一个socket地质结构变量，他指定对方的socket地址，对于面向连接的TCP协议，该成员没有意义，必须被设置为NULL，
```c++
struct iovec
{
	void* iov_base;	//内存起始地址
	size_t iov_len;	//这块内存的长度
}
```
- msg_control 和 msg_controllen 成员用于辅助数据的发送，后面再说
## SOCKET 选项
- 我们直到在文件IO中，我们可以用fcntl来控制文件描述符的属性，在socket中我们当然也可以
```c++
int getsockopt(int sockfd,int level,int option_name,
			  void* option_value,socklen_t* restrict option_len );
int setsockopt(int sockfd,int level,int option_name,
			  const void* opeion_value, socklen_t option_len );
```

```
	level //表示你需要操作的协议
	详情略 请见本书 P88
```

```c++
但这里介绍一下，当我们的服务器因为一些特殊原因关闭时，会处于TIME_WAIT状态，此时我们再创建套接字会失败，此时我们可以使用 SO_REUSEADDR 选项，可以强
制使用处于TIME_WAIT的状态的套接字。
setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
``