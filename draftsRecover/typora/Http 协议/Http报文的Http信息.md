#### HTTP 报文内的 HTTP 信息

- HTTP 报文
  - 用于 HTTP 协议交互的信息被称为 HTTP 报文。
    - 请求端 ( 客户端 ) 的 HTTP  报文叫做请求报文
    - 响应端 ( 服务器端 ) 的叫做 响应报文
  - HTTP  报文大致可以分为 报文首部和报文主体两块。
  - ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2019-34-33%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

####  编码提升传输速率

- 报文主体和实体主体的差异
  - 报文 ( message )
    - 是 HTTP 通信的基本单位，由 8 位组字节流 ( octet sequence, octet 是 8 个比特)组成，通过 HTTP 通信传输。
  - 实体 ( entity )
    - 作为请求或响应的有效载荷数据 ( 补充项 ) 被传输，其内容由实体首部和实体主体组成。
- 压缩传输的内容编码
  - 向待发送邮件内增加附件时，为了使邮件容量变小，我们会先用 ZIP 压缩文件之后再添加附件发送。
    - 内容编码指明应用在实际内容上的编码格式，并保持实体信息原样压缩。内容编码后的实体由客户端接受并负责解码
      - gzip ( GNU zip )
      - compress ( UNIX 系统的标准压缩 )
      - deflate ( zlib )
      - identity ( 不编码 )
  - 分割发送的分块传输编码
    - 在传输大容量数据时，通过把数据分割成多块，能够让浏览器逐步显示页面。
    - 这种把实体主体分块的功能称为 分块传输编码 ( Chunked Transfer Coding )
    - ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2019-47-33%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
    - 分块传输编码会将实体主体分为多个部分。每一块都会用十六进制来标记块的大小。而实体主体的最后一块会使用 " 0(CR+LF)" 来标记。

#### 发送多种数据的多部分对象集合

- 发送邮件时，我们会在邮件中写入文字并添加多份附件。这是因为采用了 MIME ( MUltipurpose Internet Mail Extensions, 多用途网络邮件扩展 ) 机制，他允许邮件处理文本，图片，视频等多个不同类型的数据。
- 多部分对象集合包含的对象如下
  - multipart / form-data
    -  在 web 表单文件上传时使用
  - multipart / byterangers
    - 状态码 206 ( Partial Content , 部分内容 ) 响应报文包含了多个范围的内容时使用。

#### 获取部分内容的范围请求

- 在过去，网速不是那么快，下载一个比较大的图片就已经比较吃力了，如果下载过程中，出现了网络问题，那简直是灾难。就必须要重新开始。
- 为了解决上述问题，需要一种可恢复的机制。就是能从之前下载中断处恢复下载。
- 要实现该功能需要指定下载的实体范围
  - 指定范围发送的请求叫做范围请求 ( Range Request )
- 执行范围请求时，会用到 首部字段 Range 来指定资源的 byte 范围
  - ![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2020-06-16%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
  - 针对范围请求，响应会返回 状态码为 206 Partial Content 的响应报文。另外对于多重范围的范围请求，响应会在首部字段 Content - Type 标明 multipart / byteranges 后返回响应报文。
  - 如果服务器端无法响应范围请求，则会返回状态码 200 OK 和完整的实体内容

#### 内容协商返回最合适的内容

- 一个网页往往对应着多种语言，在不同的区域访问时，会显示不同的页面。
  - 这样的机制称为 内容协商 ( Content Negotiation )
- 内容协商机制是指客户端和服务器端就响应的资源内容进行交涉，然后提供给客户端最为合适的资源。内容协商会以响应资源的语言,字符集，编码方式等作为判断的基础。
- 包含在请求报文中的某些首部字段 ( 如下 ) 就是判断的基准。
  - Accept
  - Accept-Charset
  - Accpet-Encoding
  - Accept-Language
  - Content-Language
- 内容协商技术有以下三种类型
  - 服务器驱动协商 ( Server - driven  Negotiation )
  - 客户端驱动协商 ( Agent - drivent Negotiation )
  - 透明协商 ( Transparent Negotiation )

















































































































