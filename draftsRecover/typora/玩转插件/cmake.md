#### CPP 是一门和操作系统密切相关的语言，每个平台都有自己的一套构建工具

- windows--> visual studio / msbuild
- mac os --> xcode / xcodebuild
- linux --> Makefile
- … --> …

#### 这些在不同平台有着不同的构建方式，实在是让开发人员很头疼，而 Cmake 的出现则减轻了一些。
---
- 1. cmake 中指令大小写无关，参数和变量大小写相关。
- 2.变量使用<font color = red> $ { } <font color = black>来取值。
#### 重要指令和 CMake常用变量
- cmake_minimum_required ***
	- 指定CMake的最小版本要求
```cmake
cmake_minimum_required(VERSION 2.8.3)
```
- project  
	- 定义工程名称，并可指定工程支持的语言
	- project(projectname [c++] [c] [java])

```cmake
project(HELLOWORLD)
```
- set
	- 显示的定义变量
	- set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
```cmake
# 定义 SRC 变量，其值为 main.cpp hello.cpp
set (SRC sayhello.cpp hello.cpp)
```
- include_directories 向工程中添加多个特定的头文件搜索路径 ---> 相当于 指定 g++ 编译器的 -l 参数
	- 语法 : include_directories([AFTER | BEFORE] [SYSTEM] dir1 dir2 ... )
```cmake
# 将 usr/include/myincludefolder 
include_directories(/usr/include/myincludefolder ../include)
```
- link_directories 
	- 向工程中添加多个特定的库文件搜索路径
```cmake
# 将 /usr/lib/mylibfolder  和 ./lib 添加到库文件搜索路径
link_directories(/usr/lib/mylibfolder ./lib)
```
- add_library
	- 生产库文件
	- add_library(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] source1 source 2 ... sourceN)
```cmake
# 通过变量 SRC 生成 libhello.so
add_library(hello SHARED ${SRC})
```
- add_complie_options
	- 添加编译参数
	- add_compile_options(<option> ...)
```cmake
# 添加编译参数 -wall -std=c++11
add_compile_options(-wall -std=c++11 -02)
```
- add_executable
	- 生成可执行文件
	- add_library(exename source1 source2 ... sourceN)
```cmake
# 编译 main.cpp 生成可执行文件
add_executable(main main.cpp)
```
- target_link_libraries
	- 为target添加需要链接的共享库
	- target_link_libraries(target library1<debug | optimized > library2...)
```cmake
# 将hello动态库文件链接到可执行文件main
target_link_libraries(main hello)
```
- add_subdirectory
	- 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
	- add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```cmake
# 添加src子目录，src中需要有一个CMakeLists.txt
add_subdirectory(src)
```
- aux_source_directory
	- 发现一个目录下所有源代码的文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表。
	- aux_source_directory(dir VARIABLE)
```cmake
# 定义SRC变量，其值为当前目录下所有的源代码文件
aux_source_directory(. SRC)
# 编译SRC变量所代表的源代码文件，生成main 可执行文件
add_executable(main ${SRC})
```
----
### CMake 常用变量
- CMAKE_C_FLAGS gcc 编译选项
- CMAKE_Cxx_FLAGS g++ 编译选项
```cmake
# 追加 -std=c++11
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```
- CMAKE_BUILD_TYPE 编译类型 ( Debug, Release )
```cmake
# 设定编译类型为debug, 调试时需要选择 debug
set( CMAKE_BUILD_TYPE Debug)
# 设定编译类型为release, 发布时需要选择release
set(CMAKE_BUILD_TYPE Release)
```


