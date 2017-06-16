Liunx Note
== 
###  c语言基础
- [数据类型](https://github.com/drsin/linuxCoreLearn/tree/master/c/dataType)
- [输入输出](https://github.com/drsin/linuxCoreLearn/tree/master/c/PrintSacnf)
- [基础练习](https://github.com/drsin/linuxCoreLearn/tree/master/c/baePractice)
- [系统调用](https://github.com/drsin/linuxCoreLearn/tree/master/c/sysCall)
### liunx shell
- kernel的版本	
```
uname -a 可以查看linux内核版本
X-window 下创建的终端是虚拟终端
```
- 配置网络
```
vim /etc/sysconf/network-script/ifcfg-eth0
如果想使用图形化界面setup
```
- man linux中的帮助手册

```
分为8章： 		
第1章 Linux系统命令的帮助 	
第2章 Linux系统API的帮助手册		 		
第3章 C库函数的帮助 		
第5章系统配置文件的帮助 		
第7章 某一主题的帮助 		
第8章 系统管理的命令 
命令组成 cmd [option [argument]]
```

- pwd命令，查看当前路径
- ls 查看目录下的文件

```
单敲一个ls，只显示当前目录下的文件 	默认不显示隐藏文件，想显示用-a选项 	
-d显示目录本身的信息 	多个选项可以合并着写 -ld
一个目录创建后，会自动创建两个目录，
.  代表本目录 	.. 代表上级目录 	最顶层的..就是自身
```

- mv 文件的移动或改名
- cp source dest 把source拷贝到dest

```
-r 拷贝目录
```
	
-  touch 创建文件

```
更新文件最后修改时间
```
	
- cd改变当前目录到制定的目录
- mkdir 创建目录
- rmdir 只能删除空目录
- rm -rf 删除非空目录

- cat 显示文件的内容
- more 分屏显示文件内容,空格显示下一屏，b上一屏
- alias 起别名
```
linux有个习惯：在终端设置的信息只在本终端有效，离开终端就无效,如果想让设置永久生效，得修改配置文件,但是不立即生效，下一次用就生效了
```

- useradd 用户名 添加新用户
- passwd 修改用户密码
- userdel -r 删除用户

- hostname
- id显示用户信息
- whoami
- date 显示时间

- shutdow -h now 发送广播信息
-  init 0   关闭系统的所有服务
- halt -p  关闭电源
- shutdown -r now 
- init 6
- reboot


- 创建一个用户

```
在/home/创建一个目录,并且添加一些隐藏文件,这些隐藏文件来自/etc/skel/.*  
chown -R xiaoyan.xiaoyan  .
在/etc/passwd文件中添加一行记录
在/etc/shadow文件中添加一条记录
在/etc/group中添加一条组的信息
在/etc/gshadow文件中添加一条记录
```

- groupadd 

```
将一个用户加入到一个组，在group文件中对应的组后面添加上用户名，如果添加多个用户用逗号分割，
 管理员的组id等于0，其他用户加入到这组也不是管理员
```

- -rw-r--r--. 1 root    root     1045 7月  15 14:13 day02.txt

```
第一列 文件的类型
普通文件
d 目录文件
l 软链接文件
p 管道文件
b 块设备文件
c 字符设备文件
s socket文件	
  own        grp       othr
  r w -     r - -     r - -
  | | |
  | | |
  | | \_执行
  | \___写
  \_____读
```

- chmod 修改文件的权限

```
 chmod 谁-/+/=权限  文件
		  o       r
          g       w
          u       x
          a
	+ 在原有的权限基础上添加新的权限
	- 在原有的权限基础上取消对应的权限
	= 取消原有权限设置为新的权限

	t 粘帖位
	s 用户设置位
	
```
	程序在执行过程中存在两个用户:实际用户,有效用户

	- 硬链接数
		硬链接文件不能跨分区

- which 查找命令在哪里
- whereis 查找命令在哪里，比which多了关于帮助的位置

- find 找文件	

```
	-name
	-type
	-user
	-group
	-mtime
		+n 更新时间距离现在n天前
		-n 更改时间距离现在n天内
	多个查找条件可以用 -a -o
- grep 查找文件中的内容
	如果要递归查找子目录 -r
```

- tar 打包

```
	tar -cvf 打包
	gzip 压缩成 tar.gz
	bzip2 压缩程 tar.bz2

	tar -jcvf tar.bz2
	tar -zcvf tar.gz
```


- head 显示文件的开始若干行,默认10行
- tail 显示文件末尾的若干行

- cut 显示文件某些列 -d列的分割符号 -f要显示的列
- sort -t -k -n

- uniq 过滤相邻的重复行

- wc 用于统计行数，单词数，字符数
	 -l
	 -c
	 -w

- sed 流式编辑器
	

```
 逐行读取文件中的内容存储到临时缓存，接着用sed命令处理缓存中的内容，处理完成以后，把缓存中的内容送到屏幕，接着处理下一行，直到文件末尾，对源文件的内容没有改变。
 -n 不打印 	
用法 sed [选项] 命令 文件 
	sed '4,$d' day03.txt 	从第4行到最后一行删除 
	sed '3q' day03.txt 		处理完第三行时退出 	
	sed 's/3/三/' note.txt 		将每行的第一个3替换成三
	sed 's/3/三/g' note.txt 		将所有的3替换成三
```

- awk 处理数据和生成报告的编程语言	

```
awk比sed多了列处理功能

awk [option] awk_script files
	-F 指定输入记录分段的分割符
	-f 从指定的awk脚本读

awk -F: '{print $1}' /etc/passwd

		awk -F: 'BEGIN{}
		/pattern/{}
		END{}'  /etc/passwd

正则表达式
	\<\>匹配单词
	.* 任意多个任意字符
	.  任意单个字符
	^  行首
	
输入输出重定向
ls 从磁盘读，向屏幕写
cat 从文件读，向屏幕写

输入：数据来源
输出：数据去向
我们将有输入输出的命令叫过滤器

标准的输入 0 stdin
标准的输出 1 stdout
标准的错误 2 stderr

改变输入输出方向叫重定向
```

- 进程优先级 nice 
	

前后台进程

	&  把进程放入后台
	jobs 查看后台有哪些进程
	fg %i 把i号进程从后台搬到前台
	ctrl+z 把前台进程拿到后台
	bf %i 将后台i号进程运行起来

	如果想在离开shell终端时，后台进程继续运行
	nohup


