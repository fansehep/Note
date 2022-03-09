- 我们来看看 Nginx 的程序目录
- ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2022-01-08%2014-43-57%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
- conf :
  - CGI ( Common Gateway Interface )通用网关(接口)，主要解决的问题是从客户端发送一个请求和数据。服务端获取到请求和数据后可以调用 CGI程序处理及相应结果给客户端的一种标准规范。
  - fastcgi.conf :  fastcgi 相关配置文件
  - fastcgi.conf.default : fastcgi.conf 的配置文件
  - fastcgi_params : fastcgi 的参数列表
  - fastcgi_params.default : fastcgi 的参数备份文件
  - scgi_params : scgi 的参数文件
  - scgi_params.default : scgi 的参数备份文件
  - uwsgi_params : uwsgi 的参数文件
  - uwsgi_params.default : uwsgi 的参数备份文件































