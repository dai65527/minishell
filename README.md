# minishell
A small shell implementation

# how to use

## build
Just execute `make` to compile and build minishell

## execute
Just execute `./minishell`

```
$ ./minishell
$ ./minishell 
              _       _      __         ____   ____ 
   ____ ___  (_)___  (_)____/ /_  ___  / / /  / __ \
  / __ `__ \/ / __ \/ / ___/ __ \/ _ \/ / /  / / / /
 / / / / / / / / / / (__  ) / / /  __/ / /  / /_/ / 
/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/  /_____/  
                               by Dhasegaw & Dnakano
                                                    
              ____----------- _____
\~~~~~~~~~~/~_--~~~------~~~~~     \
 `---`\  _-~      |                   \
   _-~  <_         |                     \[]
 / ___     ~~--[""] |      ________-------'_
> /~` \    |-.   `\~~.~~~~~                _ ~ - _
 ~|  ||\%  |       |    ~  ._                ~ _   ~ ._
   `_//|_%  \      |          ~  .              ~-_   /\
          `--__     |    _-____  /\               ~-_ \/.
               ~--_ /  ,/ -~-_ \ \/       __________---~/
                  ~~-/._<   \ \`~~~~~~~   |_42_|  ##--~/
                         \    ) |`------##---~~~~-~  ) )
                          ~-_/_/                  ~~ ~~
minishell $
```

# functions
## execute nornal comand
You can execute commands or executables by absolute/relative path or command name if it's included in PATH.
```
minishell $ ls -l
total 120
-rwxr-xr-x    1 dnakano  staff   3171  2 28 18:53 Makefile
drwxr-xr-x    4 dnakano  staff    128  2 28 18:53 includes
drwxr-xr-x  171 dnakano  staff   5472  2 28 18:53 libft
-rwxr-xr-x    1 dnakano  staff  53532  2 28 18:53 minishell
drwxr-xr-x  107 dnakano  staff   3424  2 28 18:53 srcs
```

## built in command
### echo
`echo` command with or without -n option is implemented.

```
minishell $ echo hello minishell!!
hello minishell!!
minishell $ echo -n hello minishell!!
hello minishell!!minishell $
```

### cd/pwd
You can change direcory by built in `cd` commnand and `pwd` command displays the current directory.

```
minishell $ pwd  
/path/to/repsitory/minishell
minishell $ cd srcs     
minishell $ pwd
/path/to/repsitory/minishell/srcs
minishell $ cd /
minishell $ pwd
/
```

### export/unset/env
You can add/delete environmental varibles by `export`/`unset` command. `env` command also works.

```
minishell $ echo $HELLO

minishell $ export HELLO=WORLD
minishell $ echo $HELLO
WORLD
minishell $ unset HELLO  
minishell $ echo $HELLO

minishell $ unset PATH
minishell $ ls
minishell: ls: command not found
```

## Other features
### redirection (`>`, `>>`, `<`)
```
minishell $ echo hello minishell!! > file   
minishell $ cat file
hello minishell!!
minishell $ cat filenotexist >> file
cat: filenotexist: No such file or directory
minishell $ cat filenotexist 2>> file
minishell $ cat file
minishell $ cat < file
hello minishell!!
cat: filenotexist: No such file or directory
```

### pipes

```
minishell $  cat includes/minishell.h | grep int | wc -l
      53
minishell $ echo hello minishell | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat
hello minishell
```
