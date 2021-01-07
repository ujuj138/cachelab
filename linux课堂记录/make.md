##make

>[视频](https://www.bilibili.com/video/BV1hE411N7BK?from=search&seid=16035044015863469012)

####ex1

+ `touch main.c tool1.c tool2.c tool1.h tool2.h`

+ main.c

```main函数

	#ifdef TOOL1_H_
	
	#define TOOL1_H_

	#endif

	#include<stdio.h>

	main(){}

```

+ makefile

```
	
OBJS=main.o tool1.o tool2.o #用以代替下方的内容
CC=gcc #使用$()来获取
CFLAGS+=-c -Wall -g#当需要字符串组合时使用+

	mytool:main.o tool1.o tool2.o
		gcc main.o tool1.o tool2.o

	main.o:main.c
		gcc main.c -c Wall -g -o main.c

	tool1.o:tool1.c
		gcc tool1.c -c Wall -g -o tool1.c

	tool2.o:tool2.c
		gcc tool2.c -c Wall -g -o tool2.c
	
	clean:
		rm *.o mytool -rf

```

+ include 参与所欲不需要依赖h文件

+ 执行clean 使用`make clean`

+ $^ 表示本部分被依赖的部分， $@表示本部分被生成的部分

+ `%.o:%.c`	`$(CC) $^ $(CFLAGS) -o $@`
> %的用法