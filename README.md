# minishell
In this group project, we will write a program in C that resembles bash.<br />
Program name | minishell |
|:--- |:---
Turn in files | [Makefile](https://github.com/merijnjong/minishell/blob/main/minishell/Makefile), [minishell.h](https://github.com/merijnjong/minishell/blob/main/minishell/incs/minishell.h), [minishell.c](https://github.com/merijnjong/minishell/blob/main/minishell/srcs/minishell.c), in directory minishell/ |
Makefile | NAME, all, clean, fclean, re |
Arguments |  |
External functions | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,<br />add_history, printf, malloc, free, write, access, open, read, close, fork,<br />wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset,<br />kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe,<br />opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl,<br />getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
Libft authorized | yes |
Description | Write a shell |

### Instructions
Your shell should:
• Display a prompt when waiting for a new command.<br />
• Have a working history.<br />
• Search and launch the right executable (based on the PATH variable or using a<br />
relative or an absolute path).<br />
• Avoid using more than one global variable to indicate a received signal. Consider<br />
the implications: this approach ensures that your signal handler will not access your<br />
main data structures.<br />
Not interpret unclosed quotes or special characters which are not required by the<br />
subject such as \ (backslash) or ; (semicolon).<br />
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-<br />
characters in the quoted sequence.<br />
• Handle " (double quote) which should prevent the shell from interpreting the meta-<br />
characters in the quoted sequence except for $ (dollar sign).<br />
• Implement redirections:<br />
◦ < should redirect input.<br />
◦ > should redirect output.<br />
◦ << should be given a delimiter, then read the input until a line containing the<br />
delimiter is seen. However, it doesn’t have to update the history!<br />
◦ >> should redirect output in append mode.<br />
• Implement pipes (| character). The output of each command in the pipeline is<br />
connected to the input of the next command via a pipe.<br />
• Handle environment variables ($ followed by a sequence of characters) which<br />
should expand to their values.<br />
• Handle $? which should expand to the exit status of the most recently executed<br />
foreground pipeline.<br />
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.<br />
• In interactive mode:<br />
◦ ctrl-C displays a new prompt on a new line.<br />
◦ ctrl-D exits the shell.<br />
◦ ctrl-\ does nothing.<br />
• Your shell must implement the following builtins:<br />
◦ echo with option -n<br />
◦ cd with only a relative or absolute path<br />
◦ pwd with no options<br />
◦ export with no options<br />
◦ unset with no options<br />
◦ env with no options or arguments<br />
◦ exit with no options<br />

