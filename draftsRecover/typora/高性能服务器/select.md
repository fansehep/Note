## Select

```c
int select(int n,	// n 等待测试的文件描述符基数，他的值是待测试的最大描述符 +1
           fd_set* readset,// 读 描述符 集合
           fd_set* writeset,// 写 描述符 集合
           fd_set* exceptset,// 异常描述符 集合
           const struct timeval* timeout);// select 函数的超时时间，等待多久即放弃
```

- Select是为了解决多个文件描述符读写的问题。

- ```c
  struct timeval
  {
    long tv_sec;	// s
    long tv_usec;	// ms
  };
  ```

- select 函数超时返回 0, 失败返回 -1，成功返回大于 0 的整数

  - 该整数即是就绪文件描述符的数目

- 宏函数

  - ```c
    #include <sys/select.h>
    // fdset 变量的所有位设为 0 
    int FD_ZERO(int fd, fd_set* fdset);
    // 清楚某个位
    int FD_CLR(int fd, fd_set* fdset);
    // 设置变量的某个设置位
    int FD_SET(int fd, fd_set* fd_set);
    // 测试某个位是否被置位
    int FD_ISSET(int fd, fd_set* fdset);
    ```

- fd_set 应该是一个位图

- file_operations

  - select poll epoll 不能监听普通文件，即不提供 poll 接口的文件，都不能被 select poll epoll 所监听。

  - 对于 epoll_ctl 而言，系统调用内部，会调用一个 poll函数，但是linux使用的是ext4文件系统，ext4 文件系统对于普通文件不支持 poll回调。

  - Linux 对文件的操作做了很高层的抽象，它并不知道每种具体的文件应该怎样打开，读写。Linux让每种设备类型自己实现 struct file_operations 结构体中定义的各种函数.

    ```c
    struct file_operations {
      loff_t (*llseek) (struct file*, loff_t, int);
      ssize_t (*read) (struct file*, char __user *, size_t, loff_t*);
      ssize_t (*write) (struct file*, const char __user *, size_t, loff_t*);
      unsigned int (*poll) (struct file*, struct poll_table_struct*);
      //...
    }
    ```

  - 不是所有的文件类型都支持 select/poll/epoll 函数，比如普通文件类型就不支持。为了支持epoll等函数，文件类型必须实现 file_operations 函数列表中的 poll 函数。

    - ！！！ 注意这里的poll函数并不是IO多路复用的poll函数
    - poll 函数的作用
      - 1. 将当前线程加入到设备驱动的等待队列，并设置回调函数。这样设备上有事件发生时才知道唤醒通知哪些线程，调用这些线程用的什么方法。
        2. 检查此刻已经发生的事件， POLLIN, POLLOUT, POLLERR等，以掩码形式返回。

- 等待队列

  - 等待队列是 Linux 内核中非常核心的数据结构，在异步事件通知，夸进程通信中广泛使用。

    ```c
    struct wait_queue_entry{
      unsigned int 		flags;
      void*				private;	//* 指向等待队列的进程 task_struct
      wait_queue_func_t func;		//* 唤醒时执行的函数
      struct list_head  entry;		//* 链表元素
    };
    struct wait_queue_head{
      spinlock_t lock;
       struct list_head head;
    };
    struct list_head{
      struct list_head* next, *prev;  //* 双向链表
    };
    ```

    





