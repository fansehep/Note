### MapReduce

- MapReduce 是 Google 于 2004 年提出的一种分布式任务框架。

  - 论文链接 chrome-extension://bocbaocobfecmglnmeaeppambideimao/pdf/viewer.html?file=http%3A%2F%2Fnil.csail.mit.edu%2F6.824%2F2020%2Fpapers%2Fmapreduce.pdf

- 其主要思想则是 : 

  - map(k1 , v1)   ----> list(k2, v2)
  - reduce(k2, list(v2)) ----> list(v2)

- 我们将多个任务不在单机执行，将其分配到多个worker中。

  - 在这些分配的过程，我们发现他们满足某种<key, value> 键值对的关系。
  - 但是由于在多机运行，我们必须要考虑一些同步的问题。

- 我在 6.824 中的实现

  - 6.824 已经帮助我实现了大致框架，并且已经给了我 RPC 调用的方法。
  - 所以我只需要实现 leader 和 多个 worker 之间的通信和同步问题即可。

- Coordinator 

  ```go
  //* master 节点
  type Coordinator struct {
  	//* worker 的个数
  	WorkerNum       int
  	//* 保存每个worker的个数
  	WorkerState     []int // -1 - dead, 0 - idle, 1 - working
  	//* 记录每个worker 心跳
  	WorkerCallTime  []int
  	//* 执行map函数时的状态
  	MapTaskState    []int // 0 - no allocate, 1 - dealing, 2 - completed
  	//* 执行reduce函数的状态
  	ReduceTaskState []int // 0 - no allocate, 1 - dealing, 2 - completed
  	//* 保存传入的文件名称
  	Filename        []string
  	//* 记录 map 任务分配给了哪个worker
  	Map2Worker      []int
  	//* reduce 桶的个数
  	nReduce         int
  	//* 记录 reduce 任务分配给了哪个worker
  	Reduce2Worker   []int
  	//* 互斥锁
  	mux             sync.Mutex
  }
  ```

- worker 

  - 1. 先 GetId

    2. 处于一个循环之中，不断获取任务

       ```go
       type GetTaskArgs struct {
       	ID int
       }
       
       type GetTaskReply struct {
       	TaskType     int // -1 - exit, 0 - idle, 1 - map task, 2 - reduce task
       	MapTaskID    int
       	MapFilename  string
       	ReduceTaskID int
       	ReduceNum    int
       	MapNum       int
       }
       ```

    3. 获取任务之后分别判断，再进行处理即可。但在处理过程中如果失败，则要告诉master, 使得master可以重新发布任务，这里我们看下 GetTask的实现

       ```go
       func (c *Coordinator) ReduceSuccess(args *ReduceSuccessArgs, reply *ReduceSuccessReply) error {
       	c.mux.Lock()
       	defer c.mux.Unlock()
       	c.WorkerState[args.ID] = 0
       	c.WorkerCallTime[args.ID] = 0
       	c.ReduceTaskState[args.ReduceTaskID] = 2
       	c.Reduce2Worker[args.ReduceTaskID] = -2
       	c.PrintState()
       	return nil
       }
       
       func (c *Coordinator) GetTask(args *GetTaskArgs, reply *GetTaskReply) error {
       	// map task
       	c.mux.Lock()
       	defer c.mux.Unlock()
           // 假设所有的map任务都完成
       	allMapCompleted := true
       	for i := range c.MapTaskState {
               // 未分配
       		if c.MapTaskState[i] == 0 {
       			reply.TaskType = 1
       			reply.MapTaskID = i
       			reply.MapFilename = c.Filename[i]
       			reply.ReduceNum = c.nReduce
       			
       			c.WorkerState[args.ID] = 1
       			c.WorkerCallTime[args.ID] = 0
       			c.MapTaskState[i] = 1
       			c.Map2Worker[i] = args.ID
       			return nil
                   // mapfinish 函数会将c.maptaskstate[i] = 2
                   // 这里判断是为了下面reduce 函数判断
       		} else if c.MapTaskState[i] != 2 {
       			allMapCompleted = false
       		}
       	}
       	// reduce task
       	if allMapCompleted == true {
       		for i := range c.ReduceTaskState {
       			if c.ReduceTaskState[i] == 0 {
       				reply.TaskType = 2
       				reply.ReduceTaskID = i
       				reply.MapNum = len(c.MapTaskState)
       				c.WorkerState[args.ID] = 1
       				c.WorkerCallTime[args.ID] = 0
       				c.ReduceTaskState[i] = 1
       				c.Reduce2Worker[i] = args.ID
       				return nil
       			}
       		}
       	}
       	reply.TaskType = 0
       	return nil
       }
       ```

    4. 

