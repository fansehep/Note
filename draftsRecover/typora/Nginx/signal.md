### 信号编程

- linux操作系统为一个进程准备了64种信号，这不同的信号对应了不同的处理，但大多数信号的作用都是结束该进程。

  - 可重入 : 一个可以被多个任务调用的过程，任务在调用时不用担心数据是否会出错。一个可重入函数简单来说就是可以被中断的函数。
    - 一个可重入的函数简单来说就是可以被中断的函数，也就是说，可以在这个函数执行的任何时刻中断他，转入OS下去执行另外一段代码。返回时，不会出现什么错误。而不可函数由于使用了一些系统资源，比如全局变量区，中断向量表等。所以如果他被中断的话，可能会出现问题。这类函数是不能运行多任务环境下的。
    - 保证函数可重入性的方法
      - 1. 在写函数时候尽量使用局部变量(例如寄存器， 堆栈中的变量)
      - 2. 对于需要使用的全局变量要加以保护(如采取关中断， 信号量等互斥等方法)
    - 满足下列条件的函数多数是不可重入的
      - 1. 函数体内使用了静态的数据结构(变量)
        2. 函数体内调用了 malloc 和 free 等函数
        3. 函数体内调用了 标准 IO 函数。

- 注册信号函数

  ```c
  #include <signal.h>
  void (*signal(int sig, void (*func)(int)))(int);
  ```

  - signal 是一个函数，返回 void (*p) int 
  - int sig : 所需要注册信号
  - void(*func)(int) 所需要注册信号函数

- 信号集

  - linux下的一个进程，用 sigset_t 来记录当前阻塞了哪些信号

    ```c
    typedef struct{
        unsigned long sig[2];
    }sigset_t;	
    ```

  - 相关系统函数

    - sigemptyset() 将信号集中的所有位都清0,表示这60多个信号都没有来

    - sigfillset() 将信号集中所有位设置为1,与 sigemptyset() 相反。

    - sigaddset() sigdelset() 就可以往信号集中增加信号或者删除信号。

    - sigprocmask, sigmember

      - 同时会有一个信号集记录是否屏蔽(阻塞)了哪些信号

      - 如果将这个信号集中某个信号位设置为1, 就表示屏蔽了该信号

        ```c
        int sigprocmask(int how, const sigset_t* set, sigset_t* oset);
        // how : 如何处理set and oset 这两个信号集合
        // set : new sigset
        // oset : old sigset
        // sigprocmask 设置当前进程所对应的信号就
        ```

        





















