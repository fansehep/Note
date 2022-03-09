- # 1.pipe
```c++
	#include <unistd.h>
	int pipe( int fd[2] );
```
- **pipe**函数会创建一个管道，我们规定数据只能从 fd[1] 中写入，只能从 fd[0] 中读出。
```c++
	int socketpair(int domain,int type,int protocol,int fd[2]);
	//成功时返回0，失败时返回1。
```
- # 2.dup and dup2
```c++
int dup(int file_descriptor);
int dup2(int file_descriptor_one,int file_descriptor_two);
```
- dup函数会创建一个新的文件描述，该文件描述符和原文件描述符指向相同的文件，管道，或者网络连接，dup总是返回系统中最小的可用文件描述符
- dup2和dup类似，但他将返回第一个不小于file_descriptor_one的整数值
- dup和dup2函数调用失败就会返回-1并设置errno
- # 3.readv 和 writev
- readv函数会将数据从文件描述符读到分散的内存块中，writev则会将多块分散的内存数据一起写入文件描述符中，即集中写。
```
#include <sys/uio.h>
ssize_t readv(int fd,const struct iovec* vector,int count);
ssize_t writev(int fd,const struct iovec* vector,int count);
```
- fd的参数是被操作的目标文件描述符，vector参数的类型是iovec结构体数组，
- # sendfile 
```c++
	ssize_t senfile(int out_fd,int in_fd,off_t* offset,size_t count);
// out_fd  表示待写入内容的文件描述符
// in_fd   表示待读出内容的文件描述度
// count   该参数指定在文件描述符in_fd 和 out_fd 之间传输的字节数
```
- sendfile函数会在两个文件描述符之间直接传递数据，完全在内核之中操作，效率很高
- 该函数成功返回传输的字节数，失败返回 -1 并设置errno，
- in_fd 必须是一个支持类似 mmap函数的文件描述符，他必须指向一个具体的文件，不能是socket 和 管道 ，out_fd 则必须是一个socket，sendfile是专门为网络传输文件所设计！！！


# mmap and munmap函数  ！！！
- 1.mmap函数用于申请一段内存空间，我们可以将这段内存作为进程间通信的共享内存，也可以将文件直接映射到其中
- 2.munmap函数则会释放由mmap创建的这段内存空间，
```c++
#include <sys/mman.h>
void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
int munmap(void* start,size_t length);
```
- start函参数允许用户使用某个特定的地址作为这段内存的起始地址，如果他被设置为NULL，那么系统自动分配一个地址，length参数指定内存段的长度，port参数用来设置内存段的访问权限，
- 以上参数详情请见 本书 P108
# splice 函数
- splice 函数用于在两个文件描述符之间移动数据，也就是 0 拷贝操作
```c++
	ssize_t splice(int fd_in,loff_t* off_in,int fd_out,loff_t*
	off_out,size_t len,unsigned int flags);
```
- fd_in 参数是待输入数据的文件描述符，如果fd_in是一个管道文件描述符，那么off_out必须设置为NULL，如果 
- fd_in 不是一个管道文件描述符时，那么off_in表示从输入数据流的何处开始读取数据。
- 好无聊这个函数