## 项目经验分享 | 杨凡: 在 CurveBs 中支持带有权限的挂载

#### About [Curve](https://www.opencurve.io/Curve/HOME) :

<div align=center> <image src="./3.png" width = 50%>

<div align=left>



Curve 是一款现代化的开源分布式存储系统，支持**块存储**(CurveBs)和**文件存储**(CurveFs)，目前作为沙箱项目托管于 **CNCF**。

目前较为主流的应用:
- 可作为存算分离形态分布式数据库 [PolarDB | PG](https://github.com/ApsaraDB/PolarDB-for-PostgreSQL) 底层存储底座，为上层数据库应用提供数据一致性保证，极致弹性，高性能HTAP。详见[PolarDB | PG 进阶部署 (CurveBs共享存储)](https://apsaradb.github.io/PolarDB-for-PostgreSQL/deploying/storage-curvebs.html)。
- 可对接Kubernetes，使用 [Curve CSI Driver](https://github.com/opencurve/curve-csi) 插件在 Container Orchestrator (CO) 与 Curve 集群中实现了 Container Storage Interface(CSI)。
- 更多详见[Curve of Github](https://github.com/opencurve/curve)。

##### Curve 架构:
<div align=center> <image src="./Curve-arch.png" width = 60%>
<div align=left>

项目名称: CurveBS支持读挂载和写挂载及读写权限转换

项目描述: CurveBS 对接 PolarDB-FileSystem时支持了单个卷的共享挂载，但是并没有限制各个挂载点的读写权限，需要支持读挂载和写挂载及读写权限转换。
现在所流行的分布式数据库存算分离，存储层和计算层分离，让底层的分布式文件系统维护数据一致性，上层计算层理论上拥有极高的弹性，在扩缩时无需维护数据一致性。这里需要一个读写节点，多个只读节点，但由于读写节点可能会宕机，此时上层应该有一个其他节点来使用读写的方式挂载。
<div align=center> <image src="./curve_db_2.jpg" width = 90%>
<div align=left>

#### 项目要求:
1. 熟悉Curve代码中相关逻辑的处理流程，并根据需求进行修改，完成单元测试，合入Curve仓库。
2. 熟悉C++软件开发，熟悉gtest等相关单元测试框架。
3. 熟悉linux上的编译，调试命令，如gcc，gdb等。

- 项目导师: [吴汉卿](https://github.com/wu-hanqing)

- 项目链接: https://summer-ospp.ac.cn/#/org/prodetail/222990283


#### 项目任务开发者:

姓名: 杨凡

GitHub: [fansehep](https://github.com/fansehep)

照片: [一张生活照](fan_photo.jpg)

学校: 西安邮电大学

- 开发详情:
该项目主要希望对现有的 CurveBs open 接口进行更改，希望client 能够以不同的权限去挂载卷，CurveBS 这里有一个中控(MDS)，我们只需要在 MDS 这里做一套完整的权限控制接口即可。

- 初识项目:
CurveBs client这里的代码整体还是很清晰明了的，可以轻松的知道一些函数的调用流程，在导师的帮助之下，我很快完成了第一个版本，但我对于```Curve```毕竟是一个新手，很多地方都没有考虑周全。刚开始做的时候，想法很简单，只需要在现有的 open 接口之上进行一些更改，让 Open接口携带上权限信息，并且更改了一系列的函数调用，让```RPCRequest```携带上权限信息，在```MDS```这里做一个简单的判断即可。但我毕竟是新手，很多地方都没有想的很全面:
例如: 在权限的信息的持久化使，我是将信息保存在内存中，但是这里的```MDS```是拥有主从机制，当```MDS```发生选举时，内存数据则就会丢失，所以必须将权限相关数据持久化到```etcd```中去。
以及我们需要一些信息来唯一标记客户端，开始的设计是使用 ```ip + port```来标记，但这里有一个难点就是RPC 所暴露出的```ip + port```是不稳定的，所以退而求其次，在MDS 这里做一些简单的单元测试。
- 项目开发:
在导师的帮助之下，我参考了```class Dlock```，在```MDS```这里，设计出了```class WriterLock```类:
  - 将获取权限的方式抽象为```Lock```接口，丢失权限的方式抽象为```Unlock```接口，client 与 MDS 权限续约的方式抽象为```UpdateLock```方法。
  - 并且将 ip + port 方式标记 client 是不易于调试的，使用```uuid```方式来标记客户端。
  - 将数据持久化到etcd，并且加一些缓存。
  ```c++
  class WriterLock : public Uncopyable {
   public:
    //...
    bool Lock(const uint64_t fileid, const std::string& clientuuid);
    bool Unlock(const uint64_t fileid, const std::string& clientuuid);
    bool UpdateLock(const uint64_t fileid, const std::string& clientuuid);
   private:
    //...
  };
  ```
- 项目优化:
1. 上一版的设计已经较为全面的，但很多地方设计不是很好，例如在```open```这里，如果当前的块文件已经被读写节点所挂载，那么再使用读写的方式挂载，却仍然可以返回文件描述符，只有当你发起一次 write 请求之后，才会在客户端这里给你返回一个权限错误，这种设计是很臃肿的，我们应该认为上层的客户端如果以错误的权限打开块文件，那么应该直接返回失败。而不是再发起 write 请求之后权限错误。

2. 整合接口，原有的 Open 接口需要融入更多的打开方式，为了兼容性, 引入```Open2```接口, 剔除原有的```struct OpenFlag```，使用默认的```int```，作为参数, 现在的使用方式也更加优雅且更加明确, 用户必须指定是否使用```CURVE_SHARED(共享模式)```亦或是```CURVE_EXCLUSIVE(互斥模式)```打开块设备:
```c++
/* curve/include/client/libcurve.h */
/* simple example: */
auto fd = Open2("I Love Curve", info, CURVE_SHARED | CURVE_RDWR);
```
<div align=center> <image src="./mds_writerlock.jpg" width = 90%>
<div align=left>


- 项目思考:
在参与的过程中，导师很健谈，耐心的指导我，并且很认真的帮我review, 这里实在是很感谢他。并且在他的指导下，我帮助社区解决了一些简单的issue。目前个人对于该项目的想法是: 过去的```struct openfalgs```实属鸡肋, 新的设计有效的拓展了现有的Open方式, 对于现有的上层应用来说, 无疑可以在数据一致性和角色控制上做得更加完美, 无需应用层自己感知心跳, 即可轻松管理。
