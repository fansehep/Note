### LuaFunction

- Lua 支持多返回值

  - ```lua
    return value_1, value_2, ... 
    ```

  - 在获取函数多返回值时，应该用特殊的方式获得。

    - ```lua
      function too0 () end
      function too1 () return "a" end
      function too2 () return "a", "b" end
      ```

    - ```lua
      x, y = foo2()	-- x = "a", y = "b"
      x = foo2()		-- x = "a", "b" 被丢弃
      x, y, z = 10, foo2() -- x = 10, y = "a", z = "b"
      ```

    - 如果一个函数无返回值或者返回值个数不够，那么Lua语言将会使用nil来补充缺失的值。

    - 表构造器会完整地的接受函数调用的所有返回值。

      ```lua
      t = {foo0()} -- t = { } t 是一个空表
      t = {foo1()} -- t = { "a" } 
      t = {foo2()} -- t = {"a", "b"}
      ```

    - 但是当多返回值函数成为表的一员时，就会值拥有返回值的第一个值。

- lua 函数同样可以支持可变长的参数函数( variadic ), 即可以支持数量可边的参数。

  - ```lua
    local function add(...)
      local sum = 0
      for _, v in ipairs{...} do
        sum = sum + v
      end
      return sum
    end
    print(add(1, 2, 3, 4, 5))
    ```

  - 比如, string.format() 就是 一个可变参数的函数，
  
    - table.pack() 是一个函数，可以将 可变参数 ... 打包起来，并且返回一个表。
    
    - 另外一中遍历函数的可变长的参数的方法是使用函数select , 函数select 总是具有一个固定的参数 selector, 以及数量可变的参数。如果selector 是数值 n, 那么函数 select 则返回 第 n 个参数后的所有参数。
    
    - ```lua
      
      local function add(...)
        local sum = 0
        for i = 1, select("#", ...) do
          sum = sum + select(i, ...)
        end
        return sum
      end
      print(add(1, 2, 3, 4, 5))
      -- --> 15
      ```
    
    - 多重返回值还涉及到一个特殊的函数 table.unpack
    
      - table.pack将函数参数转化为列表，而 unpack 则将一个列表，转换成一组返回值，进而可以作为另一个函数的参数被使用。
      - unpack 函数的人重要用途之一体现在泛形调用机制上。
  
- Lua 语言支持 尾调用消除。