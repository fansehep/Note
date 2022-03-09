### LUA

- 完整 I / O 模型

  - 1. io.open("...", "mode")

       ```lua
       io.open("filename", "mode")
       [[
       	r 只读
       	w 只写
       	a 追加
       	b 二进制文件
       	返回值是一个指针，FIFE*应该是
       ]]
       ```

    2. assert()

       ```lua
       local f = assert(io.open(filename, mode))
       ```
       
       - assert( ) 函数类似断言一样，io.open 如果打开失败的话，这个程序就挂掉了。
       
    3. 我们来看一个完整的IO读取文件操作
    
       ```lua
       local f = assert(io.open(filename, "r"))
       local t = f:read("a")
       f:close()
       print(t)
       ```
    
       - 关于冒号运算符后面再说
    
    4. IO库提供了三个预定义的c语言流的句柄，io.stdin, io.stdout, io.stderr, 
    
       ```lua
       io.stderr:write(message)
       ```
    
       - io.input 和 io.output 允许混用完整的 IO 模型和 简单 IO 模型。
    
       - 调用无参数的io.input() 可以获得当前输入流。
    
       - 调用io.input(filename) 可以设置当前输入流(类似的调用同样适用于函数io.input)
    
       - ```lua
         local temp = io.input() -- 获取当前的输入流
         io.input("newinput")	-- 打开一个新的当前输入流
         io.input():close()		-- 关闭当前流
         io.input(temp)			-- 恢复此前的输入流
         ```
    
       - ```lua
         io.read(args) -- 实际上是
         io.input():read(args) -- 的缩写
         
         io.write(args) -- 实际上是
         io.output():write(args) -- 的缩写
         ```
    
       - ```lua
         io.lines() -- 返回一个可以从流中不断读取内容的迭代器。
         [[ 
         给函数 io.lines() 提供一个文件名，它就会以只读方式打开对应的该文件的输入流，并在到达文件末尾后关闭该输入流。
         若调用时不带参数，函数io.lines() 就会从1输入流读取。
         我们也可以将io.lines() 当作句柄的一个方法。
         ]]
         ```
       
    5. io.tmpfile 返回的是一个操作临时文件的句柄，该句柄是以 读 / 写 模式打开的。当程序运行结束后，该临时文件会被自动删除
    
    6. 余下详情请见lua程序设计 P74
    
    



