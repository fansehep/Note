#### HTTP 首部

HTTP 报文结构

![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2022-26-25%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

报文首部由几个字段构成

![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2022-28-00%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

![](https://raw.githubusercontent.com/fansehep/img_HMStrange/master/2021-12-31%2022-30-08%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

HTTP 首部字段

- HTTP 首部字段传递重要信息

  - 使用首部字段是为了给浏览器和服务器提供报文主体大小，所使用的语言，认证信息等内容。

- 首部字段结构

  - 由 首部字段名 和 字段值 所构成 ，中间由 冒号 " : " 分隔

  - 例如，在 http 首部中以 Content - Type 这个字段来表示报文主体

    ```tex
    Content-Type: text/html
    ```

  - 上图中，首部字段名是 Content-Type, 字符串 text/html 是字段值。

- 4 中 HTTP 首部字段类型

  - 通用首部字段 ( General Header Fields )
    - 请求报文和响应报文双方都会使用的首部。
  - 请求首部字段 ( Request Header Fields )
    - 从客户端向服务器端发送请求报文时使用的首部。
    - 补充了请求的附加内容，客户端信息，响应内容相关优先级等信息。
  - 响应首部字段 ( Response Header Fields )
    - 从服务器端向客户端返回响应报文时所使用的首部。补充了响应的附加内容，也会要求客户端附加额外的内容信息。
  - 实体首部字段 ( Entity Header Fields )
    - 针对请求报文与响应报文实体部分使用的首部。补充了资源内容更新时间等与实体有关的信息。



我们来看看 HTTP --version = 1.1 的首部字段

- 通用首部字段

| 首部字段名          | 说明                       |
| :------------------ | :------------------------- |
| Cache-Control       | 控制缓存的行为             |
| Connection          | 逐跳首部，连接的管理       |
| Date                | 创建报文的日期时间         |
| Pragma              | 报文指令                   |
| Trailer             | 报文末端的首部一览         |
| Transfer - Encoding | 指定报文主体的传输编码方式 |
| Upgrade             | 升级为其他协议             |
| Via                 | 代理服务器的相关信息       |
| Warning             | 错误通知                   |

- 请求首部字段

  | 首部字段名 | 说明 |
  | ---------- | ---- |
  | Accep      |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |
  |            |      |

  -  还有的我就不写了。偷个懒。。。

- 非 HTTP / 1.1 首部字段
  - 这一部分内容较多 见 本书 图解 http p84





















































