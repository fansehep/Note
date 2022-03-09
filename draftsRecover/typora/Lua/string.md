### String

- lua 使用 8 个bit 来存储 char 类型。

- string.gsub(stringname, target name, needname);

  - string.gsub 能对目标选中字符串进行更改。

    ```lua
    a = "one string"
    b = string.gsub(a, "one", "another")
    print(b)
    -- b = another string
    ```

- #

  - 取字符串长度

    ```lua
    print(#a)
    -- #a = 10 without '\n'
    ```

- ..

  - .. 用来连接字符串。如果连接过程中存在数字，那么就会将数字转化为字符串。

    ```lua
    a = "123"
    b = "456"
    print(a .. b)
    -- a .. b = "123456"
    ```

  - lua 中，注意，字符串是一个不可变的量(常量)

- lua 支持使用 ' ' or " " 来声明字符串。但双引号声明的字符串中出现单引号时可以不用转义。

  - 对于长字符串，可以使用一对双方括号来声明长字符串或者多行字符串常量。

    ```lua
    page = [[ balabalabalabala]]
    page = [[
    123
    2131
    321
    ]]
    ```

  - 有时字符串中可能有类似 a = b[c[i]] 的这样的内容。可以在两个**左方** 括号之间加上任意数量的等号。如 [===[]]字符串常量只有在遇到了包含相同数量等号的两个右方括号时才会结束( ]===]).

- lua 提供了数值与字符串之间的自动转换。

  - 任何有字符串参与的算术运算都会被当作浮点运算处理。

  - 显式的将字符串转化为数值可以使用函数 tonumber

    - ```lua
      tonumber(" -3 ") -- -3
      tonumber("fff", 16) -- 4095 -- 指定进制，2进制到36进制之间的任意
      tonumber("-ZZ", 36) -- -1295
      tonumber("987", 8) -- nil -- 无效
      ```

  - tostring 则可以将数值转换为字符串

    - ```lua
      tostring(10) == "10" --> true
      ```

- string.len()

  - 返回字符串的长度

- string.rep(s, n)

  - 返回将字符串 s 重复 n 次的结果

- string.reverse()

  - 字符串翻转

- string.lower(s)

  - 返回将s 中字符串中大写字母都被转化为小写字母的副本

- string.upper()

  - 返回将s中字符串中小写字母都转化为大写字母的副本

- string.sub(s, i, j)

  - 从 字符串中提取 第 i 个 到 第 j 个字符  [i, j]
    - 负数索应同样支持，-1 表示最后一个字符。-2表示倒数第二个字符
    - ！ lua 语言中的字符串都是常量，是不可变的。string.sub() 的返回值是一个新的字符串

- string.char()

  - 接受一个或者多个数字，并将他们依次转化为对应的字符，粘贴在一起，并最终返回

    ```lua
    print(string.char(97, 98, 99, 100)) --> abcd
    ```

- string.byte()

  - 返回字符串s中的第 i 个字符的内部表示

    ```lua
    print(string.byte("abc")) --> 97 -- 默认返回第一个
    print(string.byte("abc", 2)) -->98 
    ```

  - {string.byte(s, 1, -1)} 则会创建一个由字符串s中的所有字符代码组成的表

    - 但是呢lua语言对栈区进行了限制，所以限制了一个函数的返回值的最大个数。默认最大为一百万个。

- string.format()

  - 用于进行字符串格式化和将数值输出为字符串的强大工具。

  - 相关标准遵循c语言的标准库

    ```lua
    print(string.format("pi = %.4f", math.pi)) -- pi = 3.1416
    d = 5;
    m = 11;
    y = 1990;
    print(string.format("%02d/%02d/%04d", d, m, y)) -- 05/11/1990
    ```

- 同时可以使用冒号操作符

  - 此处省略

- string.find()

  - string.find(string, targetstring)

    ```lua
    string.find("hello, world!", "wor") -- 7, 9
    string.find("hello, world!", "war") -- nil
    ```

  - 如果在指定的字符串中找到了匹配的模式，则返回模式的开始和结束位置。否则返回 nil

- string.gsub("hello, world", "l", " . ")

  - string.gsub() 则会把所有的模式用另外一个字符串替换

    ``` lua
    string.gsub("hello, world", "l", ".") -- he..o wor.d 3 
    -- 在 hello, world 中找到 l， 并且用 . 替换
    string.gsub("hello, world", "a", ".") -- hello world 0
    -- 没有匹配成功，所以返回0
    ```

  - 

  

  

  

  

  

  

  

  

  

  

  

  

  

  

  

  













