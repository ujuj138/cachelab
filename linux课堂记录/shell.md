## 常用命令

+ echo
> 用于输出字符串

+ which
> 找到命令的位置，如which echo, which yums

+ pwd
> 显示当前路径

+ cd
> change the dir

+ ls
> show all the files under the path

+ cd -
> go back to last dir

+ ls -l
> more information in ls

+ mv [a] [b]
> move something to something

+ man [command]
> see how to use command

+ >
> mean the stream into
> 
> `cat < A >> B`mean copy A to B twice

> >>mean add to, > mean refer to 

+ tail 
> show the file
> 
> `tail -n + 20 A`
> 
> [菜鸟教程](https://www.runoob.com/linux/linux-comm-tail.html)
> 
> `ls -l \ | tail -n1`

+ find 
> `find . -name "*.c"` 当前目录下后缀为.c的
> 
> `find . -type f`
> 
> `find /var/log -type f -mtime +7 -ok rm{}\`
> 
> [菜鸟教程](https://www.runoob.com/linux/linux-comm-find.html)

+ grep
> to find the string in the file


+ xdg-open 
> open the file in the OS

+ `scp -r [local file] root@[ip]:[remote file]`
> send local file to remote file

+ `scp root@[ip]:[remote file] [local file]`
> get remote file to local file

##shell脚本

+ foo=bar

+ "$foo"
> bar

+ '$foo'
> $foo

+ 在shell脚本中, "$1"表示一个参数，相当于argv[0]

+ ex1 
>`mcd(){}` mch.sh
>
>`source mch.sh`此时mcd被加入bash
>
> 使用mcd即可使用该函数

+ $_
> last argv

+ $?
> The wrong code, you can echo $? to see, zero means right

+ $$
>pid

+ $@
> when you do not know how many arg 

+ ls *.sh
> show all the sh file

+ ls project?
> show all file like project1 ..

+ tounch
> [菜鸟教程](https://www.runoob.com/linux/linux-comm-touch.html)

> 改变属性，也可以用于创建文件

+ !/usr/bin/env python

+ shellcheck
> to check the sh file

+ tldr
> like man

+ locate
> find all the thing

+ updatedb
> update the file name in the db of OS

+ grep -R
> search in this dir of something

+ histroy
> print all the command history

+ cat A | fzf


