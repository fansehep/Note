- 上次我们只是简单的安装了 Nginx ，这里我们需要对Nginx 的安装做出一些修改与限制。
- 就需要  ./configure 中的参数变动了

我们来看看一些基础的指令，详情可以 ./configure --help

- PATH 和路径相关的配置信息
- with 启动模块，默认关闭
- without 关闭模块，默认开启

- prefix=PATH
  - Nginx 的安装目录，默认是 usr/local/nginx
- sbin-path=PATH
  - 指向(执行)程序文件(nginx)的路径，默认值 <prefix>/sbin/nginx
- module-path=PATH
  - 指向nginx动态模块安装目录，默认值是<prefix>/modules
- conf-path=PATH
  - 指向配置文件(nginx.conf)的路径，默认值是<prefix>/conf/nginx.conf

- error-log-path = PATH
  - 错误日志文件信息，<prefix>/logs/error.log
- http-log-path=PATH
  - 指向访问日志文件路径，<prefix>/logs/access.log
- pid-path=PATH
  - 指向访问日志文件的路径，<prefix>/logs/access.log
- lock-path=PATH
  - 指向nginx锁文件的存放路径