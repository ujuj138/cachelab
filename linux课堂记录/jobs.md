## job

+ nohup &
> 后台运行

+ bg %1
> 重新唤起

+ fg %1
> 召唤至前台

+ kill 
> 发起信号

+ -HUP
> 挂起

+ -KILL
> 杀死

+ -STOP
> 暂停

+ htop
> 监视器

+ alias
> make a short word compared to long command string

> `alias ll = "ls -lah"`

+ dotfiles
> can search it on github and change  it.


##ssh
+ scp sth root@ip:/

+ rsync -avP . root@ip:/

####tmux
> http://www.ruanyifeng.com/blog/2019/10/tmux.html

> similar to screen

+ tmux (new - s name)
> 进入一个窗口

> 括号里新建名字

+ ctrl d
> exit

+ tmux a
> show all the sesion

+ tmux detach
> 与ctrl d一致

+ tmux attach -t [0]/name
> 杀死会话


+ tmux kill-session -t [0]/name
> 杀死会话

+ tmux split-window
> 划分上下两个

+ tmux split-window -h
> 划分左右