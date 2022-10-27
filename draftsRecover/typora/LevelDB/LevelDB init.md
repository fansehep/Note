### LevelDB 初始化流程

```c++
static Status Open(const Options& options, const std::string& name, DB** dpptr);
```

- DB 是一个纯虚基类, 具体实现是```/db/db_impl.h, /db/db_impl.cc```, 

  - Options, 是打开数据库的一些模式设置, name, 是保存数据库数据的目录, dbptr 初始化成功之后保存 LevelDB 实例. 目录下可能会有这些文件

    ````c++
    000003.log
    CURRENT
    LOCK
    LOG /* 存放日志的文件 */
    MANIFEST-0000002
    ````



