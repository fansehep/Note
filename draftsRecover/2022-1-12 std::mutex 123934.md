### std::mutex

- 对资源进行保护
  - std::lock_guard<std::mutex> 
    - Rall 手法包装的mutex,离开作用域时析构
  - std::lock(std::mutex arg1, ....)
    - 同时锁多个锁，阻塞
    - 只会都锁住，或者都没锁住，如果没有全部加锁，则释放所有锁
    - 记得对单个锁unlock
  - std::lock_guard<std::mutex> mutex_name(mutex_1, std::adopt_lock)
    - 同时锁多个锁的RALL包装的锁
    - std::lock_guard 是一个结构体对象，起一个标记作用。表示这个mutex已经被lock过，无需调用构造函数。
  - std::unique_lock 是个类模板
    - std::adpot_lock 表示mutex已经被lock了
    - std::try_to_lock 
      - 尝试用mutex的lock锁住mutex,如果失败，会立即返回。不会阻塞
    - std::defer_lock
      - 