##git

+   git config --global user.email "you@example.com"
+   git config --global user.name "Your Name"

####basic
+ git init  
> init git hub

+ git status
> show the history commit

+ git add [file]
> add new file into git "new file"

+ git commit
> Then it will ask u to type the name of commit, after that will return the hash of node/

+ git log
> `git log --all --gragph --decorate [--oneline]`

>> more powerful one 

> see the log of git

+ git cat-file -p [hash]
> show the data of commit

+ git commit -a [file]
> commit all the thing, = git add + git commit

+ git checkout [hash]
> go back to the version

> `git checkout [branch]`
>> switch to another branch

+ git diff
> show the different between commit


####branch
+ git brach -vv
> show the user

+ git branch [name]
> create branch

> can use git log to see which node the brach is referred to

+ git merge [branch] 
> merge [branch] to the branch the head refer to 

> `git merge -- continue` when the merge come cross the problem.

+ git branch -d [branch]
> delete branch

####remote

+ git remote add [name] [url]

+ git push [remote] [local branch] [remote branch]
> you can see branch in `git log --all --graph --decorate`

> ex. git pushh origin master: master

+ git clone <url> <name of dir>

 ![](http://kmknkk.oss-cn-beijing.aliyuncs.com/image/git.jpg)

+ git fetch <remoter> <new branch>
>  get all the new thing

+ git pull
> combine fetch and merge

+ ~/.gitconfig
> setting 

+ 