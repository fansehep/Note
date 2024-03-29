## Server 方向学习路线

大家好, 我是西邮 Linux 兴趣小组大三的Server 组的杨凡, 很荣幸今天能够与大家分享小组 Server 方向的学习路线.

Server 一词从表面上理解是 "服务器的意思", 相信大家肯定使用过聊天软件, 你与你的朋友之间的聊天会有 服务器这样的一个中介, 帮你转发消息. 但看似简单的聊天, 其实蕴含了巨大的乐趣. 例如微信, 微信官方技术团队有几篇文章报告过他们的服务的细节, 在除夕的时候, 大家都会不断发红包 并且 发消息 以及进行视频通话, 可以想象全中国几乎14亿此时都在请求微信的服务器, 怎么让简单的聊天服务具有高可用呢 ? 他们又是怎么处理这些请求 ? 当然此处我们可以简单的认为 微信的服务 就是向外提供 通信, 视频, 语音等等服务. 因为微信的服务器的用户是我们, 广义上来讲, 任何向外提供服务的都是 "Server", 数据库 向你的java web提供数据存取服务. 

学习并且构建这样高性能的服务则是我们的主要目标.

我个人认为该方向是一个很有意思的方向, 它向下面向操作系统, 向上则又要懂一些客户需求, 且包罗万象, 我可以肯定学习该方向可以涉及到你在大学所学的所有相关计算机课程. 无论是数据结构, 操作系统, 计算机网络, 计算机体系 都涉及. 一个高性能, 高可靠, 高可用, 稳定的服务离不开上述任何的一项.

目前的主要学习路线是 : .....

系统编程, 网络编程 是大一主要需要学习的内容, 在这一阶段, 使用操作系统提供给你的 API (系统调用) 来构建简单的单机服务. 这一阶段其实就主要会去更多的了解操作系统. 通过学习系统调用可以为后面学习操作系统打下坚实的基础. 学习怎么去读写一个文件, 怎么从网络上收发包, 怎么高效的进行 IO ?

多线程的艺术

我一向认为多线程是一门艺术, 在系统编程 && 网络编程 阶段, 可能只会构建简易的不那么高效的多线程服务, 在这一阶段, 主要学习多线程编程与网络编程的结合, 众所周知, 锁确实可以保证一个函数或者class 的线程安全, 但这样的线程安全是否对性能有影响呢? 甚至某些情况不如单线程的性能? c++ 是一门自由的语言, 他将class 的生杀大权交给程序员, 多线程的析构该如何保证线程安全? 回调不回调? 异步不异步? 协程真的是未来吗? 多线程的学问很大, 熟练的使用多线程是构建高性能单机服务的良药 .

迈向分布式

数据中心的停电虽然并不是一个常有的事件, 但一旦发生实在是让人开心不起来, 例如小刚是某某电商的一个卖家, 你准备在即将到来的双十一大赚一笔, 当晚, 很遗憾, 该电商的数据中心停电了. 小刚很伤心, 悲痛欲绝, 可见, 单机服务并不能为你提供太多的可靠性保证, 一旦发生了意外, 整个服务都会受到影响, 甚至直接导致服务不可用. 那么聪明的小刚很容易想到利用多台服务器进行合作, 一起向外提供服务, 但这件事并不是那么容易的, 网络是不可靠的, 任何一台集群中的成员都有可能在任意时间宕机, 那么如何在不可靠的网络中构建出较高性能, 高可靠的服务便是这一阶段的目标. 

阿里去 IOE, IOE 是一个简称, 是指以 IBM, Oracle, EMC 为代表的小型机, 集中式数据库, 高端存储的技术架构, I 指 IBM p 系列小型机, 操作系统是 AIX, IBM 专有的 unix 系统, O 是指 Oracle 数据库, E 是指 EMC 中高端 SAN 存储. 这是一套 IT 公司特别喜欢的技术架构. 这一套东西不便宜, 再加上当时电商业务爆炸式的增长, 阿里每年都会去大量购买这样的软件许可证和增加硬件以维护他们的业务. 但长此以往这样不是一个好的办法, 当时 阿里 与 甲骨文公司买的是 3 年无限制的 License, 据说是 3 千多人民币.

而当时开源软件的流行, 也让阿里看到了一丝曙光. 于是他们开始慢慢迁移业务, 主张使用 mysql 等等, 自建云服务, 搭建分布式服务来逐渐替换一些业务场景. 可能这也是为什么如今阿里云的技术那么强大的原因之一, 阿里云的技术也很厉害, 国内第一, 全国第三的云服务厂商.

展望未来

到了此处, 便是大千世界, 计算机是一个很庞大的领域, 而此后可以细学的方向便向我们所招手, 可以去学存储, 如 分布式文件系统, 分布式数据库, 以及现在云原生时代的降临, 各种服务都将容器化, 以及操作系统, 操作系统一向是一个非常有深度的方向, 定制化系统调用将会是一个你比别人技高一筹的秘诀.

感谢大家. 