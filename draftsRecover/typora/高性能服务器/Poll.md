## Poll

- select 已经可以处理多个 socket了，但 Poll 也可以实现同样的功能, 且调用方法十分简单

- ```c
  struct pollfd{
    int fd;	// 文件描述符
    short events;	// 对文件描述符fd感兴趣的事件
    short revents; // 文件描述符fd上当前实际发生的事件
  };
  int poll(struct pollfd* ufds, unsigned int nfds, int timeout);
  ```

- poll 函数使用pollfd 结构体来监控一组文件句柄，

  - ufds 是要监控的文件句柄集合，nfds 是监控的文件句柄数量，即前面 pollfd 结构体的数量，timeout 则是等待的毫秒数。无论文件描述符是否准备好，都即可返回。
  
  - ###### **timeout** 为负数则无线等待。timeout 为 0 表示调用后立即返回。
  
  - returnValue = 0
  
    - 表示超时之前没有任何事件发生
  
  - returnValue = -1
  
    - 表示失败
  
  - returnValue >= 0
  
    - 表示返回结构体 revents 不为0的文件描述符个数。
  
- 我们来看下 POLL 的宏

  - ```c
    #define POLLIN		0x001	//有数据可读
    #define POLLPRI		0x002	//有紧急数据可读
    #define POLLOUT		0x004	//
    
    #define POLLRDNORM	0x040	//有普通数据可读
    #define POLLRDBAND	0x080	//有紧急数据可读
    #define POLLWRNORM	0x100	//写普通数据不会导致阻塞
    #define POLLWRBAND	0x200	//写紧急数据不会导致阻塞
    
    #define POLLMSG	    0x400  // 
    #define POLLREMOVE	0x1000 //
    #define POLLRDHUP	0x2000 //
    #define POLLERR		0x008  //
    #define POLLHUP		0x010  //
    #define POLLNVAL	0x020  //
    