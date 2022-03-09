# Linux 服务器程序规范
- # 日志
	- 工欲善其事，必先利其器。服务器的调试和维护都需要一个专业的日志系统。
	- Linux提供了一个守护进程来处理系统日志----syslogd,不过现在的linux操作系统使用的都是他的升级版rsyslogd
	- 这个文件主要是在 /var/log/debug 文件
```c++
#include <syslog.h>
void syslog(int priority,const char* message,...);
// 关于 priority
#define LOG_EMEGR	//系统不可用
#define LOG_ALERT	//报警，需要立即采取行动
#define LOG_CRIT	//非常严重的情况
#define LOG_ERR		//错误
#define LOG_WARNING	//警告
#define LOG_NOTICE	//通知
#define L0G_INFO	//信息
#define LOG_DEBUG	//调试
```
- 下面这个函数可以改变syslog的默认输出方式，进一步结构化日志内容
```
void openlog(const char* ident,int logopt,int facility);
```
- ident参数指定的字符串将被添加到日志消息的日期和时间之后。详情请见本书 P116
- ## 用户信息
	- UID,EUID,GID,EGID
```c++
#include <sys/types.h>
#include <unistd.h>
	uid_t getuid();		//获取真实用户ID ，e代表有效
	uid_t geteuid();		
	gid_t getgid();
	gid_t getegid();
	int setuid( uid_t uid );
	int seteuid( uid_t uid );
	int setgid( gid_t gid );
	int setegid( gid_t gid );
```
