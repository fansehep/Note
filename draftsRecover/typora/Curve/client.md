```mermaid
classDiagram 
class FileClient {
// FileClient 给上层封装好了一层文件系统的调用
virtual int open()
一系列 文件 IO 函数
 ...
 // 文件描述符 -> 文件服务接口
 std::unordered_map < int, FileInstance* > fileserviceMap_;
}
class FileInstance {
//* FileClient 本质上还是要通过 FileInstance RPC(MDSClient)
//* finfo_ 保存了文件对应的信息
FInfo_t finfo_;
...
}
class FInfo_t {
	uint64_t id;
	...
	std::string filename;
	//我所需要增加的内容
	// 权限
	uint64_t permission
	Reader or RWriter
}
FileClient --> FileInstance 
FileInstance --> FInfo_t
class NameSpaceService {
	//* RPC 到达 MDS 所对应的接口
	void CreateFile(...);
	void OpenFile(...);
	...
}
FileInstance "RPC" o-- NameSpaceService
NameSpaceService --> CurveFS
class CurveFS {
	//* CurveFS 在这里有一个全局的引用(对象)
	//* 所有 NameSpaceService 对应的操作都由 该类完成。
	StatusCode CurveFS::OpenFile(...);
}
class FileInfo {
// /curve/proto/nameserver2.proto
// 该信息存储了client 与 server 交换文件的信息

 //* 我的修改是在这里加入, 保存当前写者的IP
  std::string RWriterIP;
}
CurveFS ..> FileInfo
```

namespace_service.h / cpp OpenFile()

​	curvefs.h / cpp OpenFile

​		curvefs.h / cpp GetFileInfo WalkPath and LookUpFile

​			namespace_storage.cpp NameServerStorageImp::GetFile() 

​				std::string out 这里其实就已经获得了fileinfo 后续的东西