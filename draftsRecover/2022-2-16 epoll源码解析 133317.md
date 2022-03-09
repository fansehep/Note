## Epoll

- 三组函数

  - ```c
    int epoll_create(int size);
    // 创建一个epoll句柄，size则用来告诉内核这个监听数目有多少
    // 同时该返回的描述符在使用完毕之后也必须关闭(close())
    ```

  - ```c
    int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
    // int epfd epoll_create() 的返回值
    // int op 你需要做什么
    	// EPOLL_CTL_ADD	注册 fd 到 epfd 中
    	// EPOLL_CTL_MOD	修改已经注册的fd的监听事件
    	// EPOLL_CTL_DEL	从 epfd 中删除 fd
    // int fd 所操作的文件描述符
    // struct epoll_event* event 
    typedef union epoll_data
    {
      void* ptr;
      int fd;
      uint32_t u32;
      uint64_t u64;  
    } epoll_data_t;
    
    struct epoll_event
    {
      uint32_t events;
      epoll_data_t data;  
    };
    ```

  - ```c
    enum EPOLL_EVENTS
      {
        EPOLLIN = 0x001,
    #define EPOLLIN EPOLLIN	// 对应的文件描述符可读
        EPOLLPRI = 0x002,
    #define EPOLLPRI EPOLLPRI // 对应的文件描述符有紧急数据可读
        EPOLLOUT = 0x004,
    #define EPOLLOUT EPOLLOUT // 对应的文件描述符可写
        EPOLLRDNORM = 0x040,
    #define EPOLLRDNORM EPOLLRDNORM	//
        EPOLLRDBAND = 0x080,
    #define EPOLLRDBAND EPOLLRDBAND
        EPOLLWRNORM = 0x100,
    #define EPOLLWRNORM EPOLLWRNORM
        EPOLLWRBAND = 0x200,
    #define EPOLLWRBAND EPOLLWRBAND
        EPOLLMSG = 0x400,
    #define EPOLLMSG EPOLLMSG
        EPOLLERR = 0x008,
    #define EPOLLERR EPOLLERR	// 对应的文件描述符发生错误
        EPOLLHUP = 0x010,
    #define EPOLLHUP EPOLLHUP	// 对应的文件描述符被挂断， 对等方关闭通道
        EPOLLRDHUP = 0x2000,
    #define EPOLLRDHUP EPOLLRDHUP	
        EPOLLEXCLUSIVE = 1u << 28,
    #define EPOLLEXCLUSIVE EPOLLEXCLUSIVE
        EPOLLWAKEUP = 1u << 29,
    #define EPOLLWAKEUP EPOLLWAKEUP
        EPOLLONESHOT = 1u << 30,
    #define EPOLLONESHOT EPOLLONESHOT
        EPOLLET = 1u << 31
    #define EPOLLET EPOLLET
      };
    ```
  
- ```c
  int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
  // epfd epoll_create 返回的文件句柄
  // events 对应的文件描述符集合
  // maxevents 失效
  // timeout : ms 
  	// timeout = 0 : 立即返回
  	// timeout < 0 : 永久阻塞
  // ReturnValue = 0 则表明已经超时
  ```

- epoll vs select vs poll

  - select/poll一个致命弱点就是当你拥有一个很大的socket集合，不过由于网络延时，任一时间只有部分的socket是"活跃"的，但是select/poll每次调用都会线性扫描全部的集合，导致效率呈现线性下降。但是epoll不存在这个问题，它只会对"活跃"的socket进行操作---这是因为在内核实现中epoll是根据每个fd上面的callback函数实现的。

- 当我们调用epoll_ctl往里塞入百万个fd时，epoll_wait仍然可以飞快的返回，并有效的将发生事件的fd给我们用户。这是由于我们在调用epoll_create时，内核除了帮我们在epoll文件系统里建了个file结点，在内核cache里建了个红黑树用于存储以后epoll_ctl传来的fd外，还会再建立一个list链表，用于存储准备就绪的事件，当epoll_wait调用时，仅仅观察这个list链表里有没有数据即可。有数据就返回，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。所以，epoll_wait非常高效。而且，通常情况下即使我们要监控百万计的fd，大多一次也只返回很少量的准备就绪fd而已，所以，epoll_wait仅需要从内核态copy少量的fd到用户态而已。那么，这个准备就绪list链表是怎么维护的呢？当我们执行epoll_ctl时，除了把fd放到epoll文件系统里file对象对应的红黑树上之外，还会给内核中断处理程序注册一个回调函数，告诉内核，如果这个fd的中断到了，就把它放到准备就绪list链表里。所以，当一个fd（例如socket）上有数据到了，内核在把设备（例如网卡）上的数据copy到内核中后就来把fd（socket）插入到准备就绪list链表里了。

- ###### epoll 底层三大数据结构

  - eventpoll 表示一个 epoll 实例
  
  - epitem 对应用户注册的fd, 对应红黑树的一个字节点
  
  - epoll_entry : 完成epitem 和 epitem 事件发生时的 callback 函数之间的关联。
  
  - epoll_create 实际上在内核创建的内部结构是 struct eventpoll, 表示一个poll实例。后续如果我们再调用 epoll_ctl 和 epoll_wait 等，都是对这个eventpoll数据进行操作。
  
    ```c
    struct eventpoll {
    	struct mutex mtx;
        // 执行epoll_wait等待的进程队列
    	wait_queue_head_t wq;
        //
    	wait_queue_head_t poll_wait;
    	// 事件就绪的fd 列表，链表的每个元素是下面的 epitem
        struct list_head rdllist;
    	rwlock_t lock;
        // 快速查找 fd 的红黑树
    	struct rb_root_cached rbr;
    	struct epitem *ovflist;
    	struct wakeup_source *ws;
    	struct user_struct *user;
        // eventpoll 对应的匿名
    	struct file *file;
    	u64 gen;
    	struct hlist_head refs;
    };
  
  
