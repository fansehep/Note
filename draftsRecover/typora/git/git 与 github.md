我们怎样将 git 与 github 连在一起呢?
- 1.创建SSH Key。在用户主目录下，看看有没有.ssh目录，如果有，再看看这个目录下有没有id_rsa和id_rsa.pub这两个文件，如果已经有了，可直接跳到下一步。如果没有，打开Shell（Windows下打开Git Bash），创建SSH Key： 
```shell
$ ssh-keygen -t rsa -C "youremail@***.com"
ssh-keygen 是一个整体
```
- 然后会有一些选项让你选，一路默认即可，无需设置密码
- id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。
---
- 2.登陆GitHub，打开“Account settings”，“SSH Keys”页面：
- 点“Add SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容：
---
- 然后在 github 创建一个新的仓库，在本地的需要推送或者绑定的目录 运行:
```git
git remote add origin git@*******
```
- 将本地的仓库的所有内容，推送到远程仓库上.
```
git push -u origin master
```

