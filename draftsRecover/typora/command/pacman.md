### 软件安装和卸载
----
```shell
# pacman -S package_name1 package_name2 ...
```
- 安装或者升级多个包

```shell
# pacman -R package_name
```
- 删除单个软件包，但是保留该软件包的依赖

```shell
# pacman -Rs package_name
```
- 删除指定软件包，以及其他所有没有被其他已经安装软件包所使用的依赖。

```shell
# pacman -Rsu package_name
```
- 删除软件包和所有依赖这个软件包的程序 
	- 该操作递归删除，谨慎
```shell
# pacman -Syu
```
- 同步本地仓库，并且升级整个系统

---
---
### 查询包数据库
| 参数 | 作用 |
|    -  |  -    |
|  -Q   |  查询本地软件包的数据库 |
|  -S   |  查询同步数据库    |
|  -F   |  查询文件数据库   |

```shell
$ pacman -Ss string1 string2
```
- 在包数据库中查询软件包

```shell
$ pacman -Qs string1 string2
```
- 查询已安装的软件包

```shell
$ pacman -F string1 string2
```
- 按照文件名查找软件库

```shell
$ pacman -Qet
```
- 罗列所有明确安装而且不被其他包依赖的软件包

```shell
$ pactree package_name
```
- 显示软件包的依赖树
----
pacman数据库通常位于 /var/lib/pacman/sync. 对于每一个在/etc/pacman.conf中指定的软件仓库， 这里都有一个一致的数据库。数据库文件夹里每个tar.gz文件都包含着一个仓库的软件包信息。例如which 包:
```shell
$ tree which-2.21-5
```

pacman 将下载的软件包保存在 /var/cache/pacman/pkg/ 并且不会自动移除旧的和未安装版本的软件包。这样做有一些好处：

```shell
$ paccache -r
```
- 删除所有缓存的版本，和已经卸载的软件包。

```shell
$ paccache -Sc
```
- 清理一些缓存和一些残留的数据库文件。

```shell
$ paccache -Scc
```
- 清空缓存中的文件，比较激进，建议不要尝试。

---
---
```shell
$ pacman -Fy
```
- 同步文件数据库

