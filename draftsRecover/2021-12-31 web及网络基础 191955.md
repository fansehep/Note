#### Http 协议结构 / http - version = 1.1

- http 协议几乎都使用的是 c / s 模型

- 通过请求和响应的交换达成通信

  - 我们来看一段请求报文

  ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2018-53-56%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

  - 我们再来看一段服务器响应报文

    ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2018-57-04%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

- http 是一种不保存状态 ,无状态的协议。 Http 协议自身不对请求与响应之间的通信状态继续保存。也就是说在 HTTP 这个级别，协议对于发送过的请求或者响应都不做持久化处理。

  - 但是随着 Web 技术的发展，引入了 Cookie 技术，有了 Cookie 再用 Http 协议通信，就可以管理状态。

- Http 方法

  - GET : 获取资源
  - POST : 传输实体主体
  - PUT : 传输文件
  - HEAD : 获得报文首部
  - DELETE : 删除文件
  - OPTIONS : 询问支持的方法
  - TRACE : 追踪路径
    - 让 web 服务器端将之前的请求通信返回给客户端
  - CONNECT : 要求使用隧道协议连接代理
    - CONNECT 方法要求在与代理服务器通信时建立隧道，实现用隧道协议进行 TCP 通信， 主要使用 SSL ( Secure Sockets Layer, 安全套接层 ) , TLS ( Transport Layer Security , 传输层安全) 协议将通信内容加密后经网络隧道传输。

  ---

  ##### http协议版本变迁

  - 最初的设计是每一次通信都需要建立连接。

  - 1.0 之后采用持久连接。

    - 只要任意一段没有明确提出断开连接，则保持住 TCP 连接状态。

  - 但是这种方式要求客户端和服务端都是持久化连接。但随之而来的问题就是请求只能依次处理
    
  - 管线化技术的出现可以做到**并行**发送多个请求，而不需要一个接一个地等待响应。
    
  - 由于 http 协议本身是无状态协议。Cookie的出现则弥补这一问题
    
    - Cookie 技术通过在请求与响应报文中写入 Cookie 信息来控制客户端的状态。
    - 
    
    
    















































