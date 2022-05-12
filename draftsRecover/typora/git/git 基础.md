---
```git
git add filename
```
- 将文件添加到工作仓库

```git
git commit -m "my first commit"
```
- -m 表示本次提交的说明,commit 表示提交更改，实际上就是把工作区的所有内容提交到当前分支。

```git
git status
```
- 看当前仓库的状态

```git
git diff
```
- 查看版本变化

```git
git log
```
- 查看历史提交

```git
git reset --hard ***
```
- 回退到某个版本

```git
git reflog
```
- 查看命令历史

```git
git checkout -- readme.txt
```
- 将readme.txt 文件在工作区的修改全部撤消:
	- 一种是readme.txt自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；
	- 一种是readme.txt已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态