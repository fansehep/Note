### PostgreSQL 开发指南

- PostgreSQL 系统是基于多进程.

  - postmaster 是中央协调进程，负责系统初始化(包括共享内存的分配和后台进程的启动)，以及关闭服务器。此外，postmaster 管理与客户端应用程序的连接，并将每个新的连接客户端分配给后端服务器进程，以代表客户端执行查询，并将结果返回给客户端。
  - 客户端应用程序可以连接到 PostgreSQL 服务器，并通过 PostgreSQL 支持的众多数据库应用程序接口之一 (libpq, JDBC, ODBC) 提交查询，这些接口作为客户端库提供。客户端应用程序的一个例子就是标准中包含的命令行 psql 程序.
  - PostgreSQL 分布, postmaster 负责处理初始的客户端连接. 为此，它不断地在一个已知的端口上侦听新的连接。
    - 当它接受到一个连接请求时，postmaster 首先执行初始化步骤，比如用户身份验证，然后分配一个空闲的后端服务器进程 (或者在需要的时候生成一个新的) 来处理新的客户端。在这个初始连接之后，客户端只与后端服务器进程进行交互，提交查询并接受查询结果。只要客户端连接处于活动状态，分配的后端服务器进程就只专用于该客户端连接。因此，PostgreSQL 对后端服务器使用了一个 " 每个连接对应一个进程 " 的模型。(one client => one process)
    - 后端服务器进程负责执行客户端提交的查询，通过执行必要的查询执行步骤，包括解析，优化和执行。每个后端服务器进程一次只能处理一个查询。一个希望并行执行多个查询的应用程序必须维护多个服务器的连接。在任何给定的时间，都可能有多个客户端连接到系统，因此多个后端服务器进程可能同时执行。
    - 除了 postmaster 和后端服务器进程之外，PostgreSQL 还利用了几个后台工作进程来执行数据管理任务，包括后台写入器，统计收集器，预写日志(WAL) 写入器 和 检查指针进程。 后台写入进程负责定期将 WAL 数据刷新到持久存储中，而 checkpointer 进程 会执行数据库检查点以加快恢复速度。这些后台进程由 postmaster 进程启动.
    - 当涉及到 PostgreSQL 中的内存管理, 我们可以识别出两种不同的类别
      - 本地内存
      - 共享内存
      - 每个后端进程都会为自己的任务分配内存，比如查询处理(如内核排序操作哈希表和临时表) 和 维护操作(如真空，创建索引).
    - 另一方面，内存中的缓冲池放置在共享内存中，以便所有进程，包括后端服务器进程和后台进程都可以访问它。共享内存还用于存储锁标和其他必须由服务器和后台进程共享的数据。
    - 由于使用共享内存作为进程间通信的媒介，一个 PostgreSQL 服务器应该运行在一个单一的共享内存机器上, 在没有第三方包的协助下，单服务器站点无法跨不共享内存的多台机器执行。然而，在每个节点上运行一个 PostgreSQL 实例. 构建一个没有共享内存的并行数据库系统是可能的; 事实上，已经有几个商业的并行数据库系统正是用这种架构构建的。

- Storage and Indexing

  - PostgreSQL 的数据布局和存储方法的目录是一个简单的和干净的实现和易于管理. 作为实现这些目标的一步。PostgreSQL 依赖文件系统文件进行数据存储(也称为 "熟" 文件), 而不是自己处理裸磁盘分区上数据的物理布局。PostgreSQL 在文件层次结构中维护一个目录列表，用于存储; 这些目录被称为表空间。每个 PostgreSQL 安装都用一个默认的表空间进行初始化，额外的表空间可以随时添加。当创建表，索引或整个数据库时，用户可以制定一个表空间来存储相关的文件。如果表空间位于不同的物理设备商，那么创建多个表空间是特别有用的，这样速度更快的设备上的表空间可能专用于访问更频繁的数据。此外，存储在单独磁盘上的数据可以更有效地并行访问。

  - 由于 PostgreSQL 和文件系统之间的冲突，PostgreSQL 存储系统的设计可能会导致一些性能限制。熟文件系统的使用导致了双缓冲，即块首先从磁盘取出到文件系统的缓存中 ( 在内核空间中 ), 然后复制到 PostgreSQL 的缓冲池中。性能也会受到 PostgreSQL 以 8 KB 块存储数据这一事实的限制, 这可能与内核使用的块大小不匹配. 在安装服务器时，可以改变 PostgreSQL 的块大小，但这可能会产生不希望的后果; 小块限制了 PostgreSQL 高效存储大元组的能力，而大块在文件的一小块区域被访问是浪费的.

  - PostgreSQL 的主要存储单元是一个表. 在 PostgreSQL 中，表中的元组存储在堆文件中。这些文件使用一种标准的页槽格式。PostgreSQL 的槽页格式如图 32.2 所示。在每个页面中，页眉后面都有一组行指针(也称为条目标识符). 行指针包含页面中特定元组的偏移量(相对于页面开始) 和 长度. 实际的元组存储在页面的末尾, 以简化插入, 当在页面中添加一个新条目时，如果所有行指针都在使用，则一个新的行指针被分配在未分配空间 (pd 下) 的开始处，而实际项存储在未分配空间的末尾(pd 上).

  - 堆文件中的一条记录由它的元组 (TID) 来标识。TID 由一个 4 字节的块 ID (制定文件中包含元组的页面) 和一个 2 字节的槽 ID 组成. slot ID 是行指针数组的索引, 行指针数组反过来被用来访问元组.

  - 由于 PostgreSQL 使用的多版本并发控制 (MVCC) 技术，一个元组可能有多个版本，每个版本都有一个相关的有效开始和结束时间. 删除操作不会立即删除元组，更新操作也不会直接更新元组。相反, 元组的删除最初只是更新有效性的结束时间, 而元组的更新会创建现有元组的新版本; 旧版本的有效性结束时间设置在新版本的有效性开始时间之前.

  - 旧版本的元组对任何事务都不再可见，之后会被物理删除; 删除会导致页面形成漏洞. 通过行指针数组访问元组的间接性允许通过移动元组来压缩这样的孔, 而不影响元组的 TID .

  - 物理元组的长度受到数据页大小的限制, 这使得很难存储非常长的元组 . 当 PostgreSQL 遇到一个大的元组无法放入页面中时，它会尝试 "TOAST" 单个大属性, 即压缩属性或将其分解成更小的块. 在某些情况下，"toast" 一个属性可能会通过压缩值来完成. 如果压缩没有将元组缩小到足以容纳到页面中 (这是经常发生的情况), 则 "toast" 属性中的数据会被属性值的引用替换; 属性值存储在页面外的一个相关联的 TOAST 表中, 大的属性值被分割成更小的块; 块大小的选择使一个页面可以容纳四个块. 每个块在相关的  TOAST 表中作为单独的行存储. toast 属性的标识符与每个块的序列号的组合上的索引允许有效地检索值。只有具有可变长度表示支持的数据类型.

  - PostgreSQL 索引是一种数据结构, 它提供了从搜索谓词到元组 id 序列的动态映射. 返回的元组旨在匹配搜索谓词，尽管在某些情况下，谓词必须在实际上重新检查，因为索引可能会返回匹配元组的超集。PostgreSQL 支持几种不同的索引类型, 包括基于用户可扩展访问方法的索引. PostgreSQL 中的所有索引类型目前都使用第 ...  节中描述的槽页格式来组织索引页中的数据.

  - PostgreSQL 支持几种不同的工作负载类型的索引. 除了传统的 b- 树，PostgreSQL 支持哈希索引和几种专门的索引方法; 广义搜索树 (GiST), 空间分割的广义搜索树(SP-GiST), 广义倒转索引(GIN) 和块范围索引(BRIN), 这对于需要全文索引，也可以支持某些模式匹配操作，如某些类似表达式的情况.

  - 哈希 : PostgreSQL 的哈希索引是线性哈希的一种实现。这样的索引只对简单的相等操作有用。PostgreSQL 使用的哈希索引的查找性能并不比 b - tree 更好. 但他的大小和维护成本要大得多. 由于缺乏预写日志，哈希索引的使用通常不被鼓励. 然而，在 PostgreSQL 10 和 11 中，哈希索引的实现已经得到了显著的改进 : 哈希索引现在支持预写日志，可以被复制, 性能也提到了提高,

  - 一些使用 GIST 索引构建的索引的例子包括 r- 树，以及用于多维立方体和全文搜索的不太传统的索引.

  - GIST 接口要求访问方法实现者只实现对被索引的数据类型的某些操作, 并制定如何在 GIST 树中排列这些数据值. 新的 GiST 方法可以通过创建操作符类来实现. 基于索引实现的搜索谓词, 每个 GIST 操作符类可能会有一组不同的策略. GIST 的索引操作符类必须提供 5 个支持函数, 例如用于测试集成成员，用于在页面溢出时拆分条目集. 以及用于插入新条目的计算成本. GIST 还允许 4 个可选的支持函数, 比如支持有序扫描, 或者允许索引包含与构建它所基于的数据类型不同的类型. 在 GIST 接口上构建的索引可能是有损的, 这意味着这样的索引可能会产生错误匹配. 在这种情况下，由索引获取的记录需要重新检查索引谓词, 而一些获取的记录可能无法通过谓词.

  - PostgreSQL 提供了几种使用 GIST 实现的索引方法, 比如多维数据集的索引, 以及存储键值对的索引. 最初的 PostgreSQL 实现 r - tree 被 GIST  操作符类所取代, 它允许 r -tree 利用 GIST 索引提供的预写日志和并发能力. 原始的 R-tree 实现没有这些特性, 这说明了使用  GIST 索引模板实现特定索引的好处.

  - 在 PostgreSQL 的表分区允许一个表被分割成更小的物理块，基于分区属性的值. 在某些场景下，分区是非常有益的; 例如, 当查询包含分区属性上的谓词, 并且匹配元组在单个分区或少量分区中时, 它可以提高查询性能. 在某些情况下, 通过添加或删除分区而不修改现有分区，表分区还可以减少批量加载和删除的开销。分区还可以使诸如 VACUUM 和 REINDEX 等维护操作更快. 此外, 分区上的索引比整个表上的索引要小. 因此它更容易装入内存。只要访问关系的大多数查询都包含分区属性上的谓词，那么对关系进行分区就是一个好主意. 否则, 访问多个分区的开销会在一定程度上减慢查询处理的速度.

  - PostgreSQL 提供了三种类型的分区表 :

    - 1. 范围分区 : 将表分区为一个或一组列定义的范围 (例如, 日期范围). 每个分区中值的范围是根据某些分区表达式分配的. 范围是连续的， 不重叠的.

      2. 列表分区 : 通过显示的列出应该出现在每个分区中的离散值集来对表进行分区.

      3. 哈希分区 : 元组根据一个哈希分区键分布在不同的分区上. 哈希分区对于没有自然分区键或关于数据分布的详细的场景非常理想.

         PostgreSQL 中的分区可以使用表继承手工实现. 然而, 实现分区的一种更简单的方式是通过 PostgreSQL 的声明式分区特性. 声明式分区允许用户通过指定分区类型和用作分区键的列或表达式列表创建分区表. 

      4. 根据选择的分区键，将新的元组路由到适当的分区. 分区键范围不能重叠. 并且必须为每个有效的键值定义一个分区. PostgreSQL 的查询规划器可以利用分区信息来消除查询处理过程中不必要的分区访问.

         不支持将表转换为分区表或将分区表转换为分区表, 但是，可以将包含数据的常规表或分区表添加为分区表的分区，或者从分区表中删除一个分区，将其转换为独立表.

  - 查询处理和优化

    - 当 PostgreSQL 接受到一个查询时，查询首先被解析为一个内部表示，这个内部表示经过一系列的转换, 产生一个查询计划，由执行者用来处理查询.
    - 查询转换的第一个阶段是重写阶段, 他负责实现 PostgreSQL 规则系统. 在 PostgreSQL 中, 用户可以创建针对不同的查询结构(如更新，删除，插入 和 选择语句 ) 触发的规则. 视图由系统通过将视图定义转化为选择规则来实现. 当接受到涉及视图上的选择语句的查询时，会触发视图的选择规则，并使用视图的定义重写查询.
    - 使用 create rule 命令在系统中注册规则，此时规则的信息存储在目录中。然后，在查询重写期间使用这个目录来揭示给定查询的所有候选规则.

  - 重写阶段首先通过触发所有适当的规则来处理所有的更新, 删除 和 插入语句. 这样的语句可能很复杂, 并且包含选择子句. 随后，触发所有只涉及选择语句的其余规则. 由于一个规则的触发可能会导致查询被重写为一个可能需要触发另一个规则的表单, 所以这些规则会在重写的查询的每个表单上反复检查, 直到到达一个固定的点, 不再需要触发更多的规则.

  - 查询规划和优化

    - 查询一旦被重写，就会进入规划和优化阶段. 在这里，每个查询块都被隔离处理. 并为其生成一个计划. 这个计划从重写查询的最内层子查询开始自底向上，一直到最外层查询块.
    - PostgreSQL 中的优化器在很大程度上是基于成本的. 其思想是生成一个估计成本最小的访问计划. 成本模型包括作为参数的顺序和随机页面获取的 I / O 成本. 以及处理堆元组, 索引元组 和 简单谓词的 CPU 成本.

  - 查询的优化可以通过一下两种方法之一来完成 :

    - 1. 标准规划器 : 标准规划器使用自下而上的动态规划算法进行连接顺序优化.
      2. 遗传查询优化器 : 当查询块中的表数量非常大时，System R 的动态规划算法变得非常昂贵. 与其他默认使用贪心或基于规则的技术的商业
    
  - 查询执行器
  
    - executor 模块负责处理优化器 产生的查询计划. 执行器基于需求驱动的管道模型. 其中每个操作符通过一组 4 个 函数 open()  => next() => rescan() => close(). PostgreSQL 迭代器有一个额外的函数 rescan(). 他用于重置子计划(比如连接的内部循环). 对参数(如索引键) 是用新值, 下面是一些重要的操作符类别 : 
  
      1. 访问方法. 访问方法是用于从磁盘检索数据的操作符, 包括堆文件的顺序扫描, 索引扫描 和 位图索引扫描.
      2. 顺序扫描 : 关系的元组从文件的第一个块到最后的最后一个块进行顺序扫描. 根据事务隔离规则. 每个元组只有在它是 '可见的' 时才会返回给调用者.
      3. 索引扫描 : 给定一个搜索条件, 例如一个范围或相等谓词, 索引扫描从关联的堆文件返回一组匹配的元组. 在典型的情况下，操作符一次处理一个元组，首先从索引中读取一个条目, 然后从堆文件中获取相应的元组. 在最坏的情况下, 这可能会导致对每个元组进行随机的页面获取. 如果使用仅索引扫描，允许直接从索引中检索数据，则访问堆文件的成本可以减轻.
      4. 位图索引扫描 : 位图索引扫描减少了索引扫描中过多随机页取的危险. 为此，元组的处理分 2 个阶段完成.
  
    - 查询处理和优化
  
      1. 第一阶段读取所有索引条目, 填充一个位图, 每个堆页包含一个位; 从索引扫描中检索到的元组 ID 用于设置相应页面的位.
      2. 第二阶段获取位被设置的堆页面, 按顺序扫描位图. 这保证了每个堆页面只被访问一次. 并增加了连续页面读取的机会. 一旦获取了堆页面, 索引谓词就会在页面中的所有元组上重新检查, 因为位被设置的页面很可能不满足索引谓词的元组.
  
    - 并行查询支持
  
      PostgreSQL 可以生成并行查询计划来利用多个 核 / CPU, 这可以显著提高查询执行性能. 然而, 不是所有的查询都能从并行计划中收益, 这可能是由于实现的限制, 也可能是因为串行查询计划仍然是更好的选择.优化器负责确定并行计划是否是更快的执行策略. 