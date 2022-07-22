- 2A Leader electron

  Raft 使用一种心跳机制来触发领导人选举.

  1. 当服务器程序启动时, 他们都是follower. 
  2. 领导人周期性的向所有跟随者发送心跳包. 来确认leader 还活着.
  3. 如果一个跟随者在一段时间内没有受到任何消息. 那么它就会认为当前系统中没有可用的领导人, 并且发起选举以选出新的领导人.

  开始一次选举过程

  1. follower 需要增加自己的当前任期号, 并且他会并行的向集群中的其他服务器节点发送请求投票的 RPC 来给自己投票. 候选人会继续保持着当前状态直到以下三件事情之一发生

     - 它赢得了此次选举
     - 其他服务器成为领导人
     - 一段时间之后没有任何一个获胜的人

  2. 每一个服务器**最多只会对一个任期号投出一张选票**.按照先来先服务的原则.一旦候选人赢得选举, 他就立即成为领导人. 然后他会向其他的服务器发送心跳消息并阻止新的选举.

     在等待投票的时候, 候选人可能会从其他的服务器接收到声明他是领导人的附加条目(AppendEntries) RPC, 如果这个领导人的任期号 > 当前的候选人,
  
  3. 候选人既没有赢得选举也没有输，如果有多个跟随者都同时成为候选人，那么选票可能会被瓜分以至于没有候选人可以赢得本次选举，那么当这种情况的时候，每一个候选人都会超时，然后，又开始增加当前的任期号来开始新的一轮选举。然后，没有其他机制的话，选票可能会被无限重复瓜分。
  
  4. raft 算法 使用 **随机选举超时时间** 的方法来确保很少会发生选票瓜分的情况。
  
     - 选举超时时间是从一个固定的区间 (150 - 300ms) 的随机选择. 

---

- 2B Log Replication

  当集群中成功选举出一个 Leader 时, 开始向外提供服务, 但只有 Leader 才会去真正响应 请求,

  - Leader 维护一个 [ ]LogEntry , 当请求到来之时, 先将该请求加入 LogNums, 再将它分发出去, 如果有半数以上的节点 返回 ok, 那么就直接退出该过程.
  - prevlogindex 由 rf.NextIndex[ ServerNumber ] 获得, NextIndex 记录每个对应的服务器 更新日志的下标
  - Follower 在受到 Leader 所发来的 AppendEntries 时 :
    - 如果 args.Term < rf.currentTerm , 此次 AppendEntries 失败.
    - 如果 args.Term > rf.currentTerm . 则 被调用方变为 Follower
    - 如果 args.PrevLogIndex > 当前服务器的日志 len(rf.lognums) - 1, 那么此次 AppendEntries 失败, 
      - 这里表明日志不匹配, 让 Leader 将之前的日志补全
    - 这里可以在 reply 的时候，加入 ConflictIndex 和 ConflictTerm , 表示不匹配的 index 和 term .
    - 然后再匹配上一次 index 的 term
      - 如果不匹配的话, 找到最后一次匹配的 index, 然后返回
    - 如果没有未匹配的 term  和 index, 则表明此次是一次正常的 AppendEntries, 
      - 此时需要校验 , Leader 所发来的 ToSaveLogEntries , 找到未匹配的断点, 截断未匹配之后的所有日志, 将 ToSaveLogEntries 加入到 rf.LogNums,
    - 如果 Leader.CommitIndex > rf.ComitIndex, 如果 LeaderCommit  < rf.lastindex , 则表明, 我可以更新我自己的 commitindex 为  LeaderCommitIndex, 否则, LeaderCommit > rf.lastindex, 则表明, 我 commit 的最大值就是 len(rf.lognums)
    - 之后便去可以 applyLogs()
  - Leader 在 AppendEntries 成功之后, 需要更新当前 Leader 所匹配的 MatchIndex, Leader.NextIndex [ ] 也要随之更新.
    - AppendEntries 失败之后, 查看 不匹配的 term 的位置, 并且更新 NextIndex, 和 MatchIndex,
    - 当有一半的 Follower AppendEntries 成功之后, 才可以 Commit 这次日志更新.
  
  日志可能的状况, 可能某个 Follower 的日志会多于当前的 Leader 
  
  例 : Leader 在发送 AppendEntries 的过程中, 发送到一半就挂了, 