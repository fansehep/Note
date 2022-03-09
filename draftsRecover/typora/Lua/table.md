### Table

- Table 是 lua 语言 最主要 唯一的数据结构。

- 使用 表 lua 可以用一种简单的统一且高效的方式表示数组集合，记录其他数据结构

- lua 语言也可以使用表来表示 包 ( package ) 和其他对象

- 当调用 math.sin() 时，我们可能认为是调用了 math库的sin函数，但实际上对于 lua语言来说，其实际含义是 " 以字符串 sin " 为健值来检索表 math

- 我们使用 构造器表达式来创建表 ( constructor expression ) 创建表

  - ```lua
    a = { }
    ```

  - 表永远是匿名的，表本身和保存表的变量之间没有固定的关系

  - 对一个表而言，当程序中不再有指向他的引用时，垃圾收集器会最终删除这个表并重用其占用的内存。

- 注意  a.x 和 a[x] 的区别

  - 实际上， a.x 表示 a[ "x" ], 即由字符串 "x" 索引的表
  - a[x] 则表示由变量 x 对应的值索引的表

- 可以使用任意类型来索引表。

  - 0 和 “0” 这两个索引的值及其对应的元素是不同的

  - 同样的 字符串 "+1" "01" "1" 指向的也是不同的元素

  - ```lua
    i = 10; j = "10"; k = "+10"
    a = {}
    a[i] = "number key"
    a[j] = "string key"
    a[k] = "another string key"
    print(a[i]) -- nummber key
    print(a[j]) -- string key
    print(a[k]) -- another string key
    print(a[tonumber(i)]) -- number key
    print(a[tonumber(j)]) -- number key
    print(a[tonumber(k)]) -- number key
    ```

    注意这一点，不然容易引起诡异的 bug

  - int 和 double 就不存在上面的问题。 由于 2 和 2.0 的 值相等，所以他们被当作索应时使用的是同一个元素。

- lua 还提供了一种初始化记录式(record - like) 表的特殊用法:

  - ```lua
    a = {x = 10, y = 20}
    ```

    上述代码等价于 : a = { }; a.x = 10; a.y = 20

    据说第一个代码速度更快，因为 第一个代码可以知道表的长度

- 遍历表

  - 我们可以使用 pairs 迭代器遍历表中的健值对

    - ```lua
      table_a = {10, print, x = 12, k = "hi"}
      for k, v in pairs(t) do
        print(k, v)
      end
      -- 1 10
      -- k hi
      -- 2 function:0x420610
      -- x 12
      ```

    - 在这个过程中，遍历元素的出现顺序是随机的。相同的程序在每次运行时也可能产生不同的顺序。

  - 对于列表而言，我们可以使用  ipairs 迭代器

    - ```lua
      table_b = {10, print, 12, "hi"}
      for k, v in ipairs(table_b) do
        print(k, v)
      end
      -- 1 10
      -- 2 function: 0x420610
      -- 3 12
      -- 4 hi
      ```

    - 但如果一个表中既含有列表，又含有健值对，那么健值对将不会被遍历。

- 安全访问

  - 当我们想确认指定的库中是否存在某个函数，如果我们确定这个库确实存在。可以直接使用 if lib.foo then ...否则就要使用 if lib and lib.foo then .. 的表达式

  - 但一般可能会这么写

    - ```lua
      zip = (((company or {}).director or {}).address or {}).zipcode
      ```

    - 或者写的更简短

      ```lua
      E = {}
      local zip = (((company or E).director or E).address or E).zipcode
      ```