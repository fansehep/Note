### 表标准库

- table.insert() 向序列中的指定位置插入一个元素。其他元素依次后移动

  - ```lua
    table.insert(tablename, index, value)
    t = {10, 20, 30}
    table.insert(t, 1, 15)
    print(t) -- t = {15, 10, 20, 30}
    ```
  
- table.remove() 则删除并返回指定位置的元素

  - ```lua
    table.remove(tablename, index)
    ```

- exercise

  - ```lua
    local sunday = "monday"
    local monday = "sunday"
    local t = {sunday = "monday", [sunday] = monday}
    print(t.sunday, t[sunday], t[t.sunday])
    -- --> monday sunday sunday
    ```

  - ```lua
    -- --> local t = {"sunday" = "monday", "monday" = "sunday"}
    --* 注意 sunday 在这里就是一个字符串，
    --* 所以第一处可以理解为 "sunday" = "monday"
    --* [sunday] 则会取sunday的值 则就是 "monday"
    --* monday 在这里也是一个变量，所以 "monday" = "sunday"
    --! 非常需要注意， 这里a.x 表示 a[ "x" ], 即由字符串 x 索应的表
    --! a[x] 则表示由变量 x 对应的值索应的表
    --print(t.sunday, t[sunday], t[t.sunday])
    ```

  - 





