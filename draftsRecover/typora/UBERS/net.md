### net

- net 的 EventLoop 类

  ```mermaid
  classDiagram
   class EventLoop{
   	//
   	//
   
  
   }
   
   class Epoll{
  
   }
  
  
   EventLoop <-- Epoll
   Channel_1<--EventLoop
   channel_2<--EventLoop
   channel_3<--EventLoop
   
   class Timer_1{
  
   }
   class Timer_2{
   }
   class Timer_3{
   }
   class TimerManager{
   }
   TimerManager *-- Timer_1
   TimerManager *-- Timer_2
   TimerManager *-- Timer_3
   EventLoop *-- TimerManager
   
   class Socket{
   / 一大堆函数
   /
   /
   /
   int fd;
   }
   Acceptor *-- Socket
   class Acceptor{
    EventLoop* loop_;
    Socket 
  
   }
  
   channel_2*-- TcpConnection_2
   channel_3*-- TcpConnection_3
   TcpConnection_1 *-- TcpServer
   TcpConnection_2 *-- TcpServer
   TcpConnection_3 *-- TcpServer
  TcpServer *-- Acceptor
   EventLoop *-- EventLoopThread
   EventLoopThread *-- EventLoopThreadPool
   EventLoopThreadPool *-- TcpServer
   class TcpServer{
   
   }
  ```

- EventLoop的构造函数

  ```mermaid
  graph TD
  A["EventLoop Constructor"] --> B["wakeupChannel->EnableEvents"]
  B--> C["更新 events_, Update()"] --> D[" addedToLoop_ = true, loop_->updateChannel()",]
  D--> F["Epoll::UpdateChannel, Update()"]
  
  
  ```

  - EventLoop::loop

  ```mermaid
  graph TD
   A["Loop"] --> B["this->epoll_->Poll(ActiveChannels_)"] 
   B-->C["获取活跃连接Epoll::epoll_wait() 给传入的ActiveChannel填充 FillActiveChannels()     ___ActiveChannel_>HandleEvent()___RunFunction(处理其他线程添加的任务) "]
  ```

  - 









