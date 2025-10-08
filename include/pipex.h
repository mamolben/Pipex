#ifndef PIPEX_H
# define PIPEX_H

/*Library standar*/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

/*Library personal*/

/* libft.c */
size_t	ft_strlen(const char *str);
char	**ft_split(const char *str, char car);
char	*ft_strdup(const char *str);
void	ft_free(char **str);

/* errors.c */
void	ft_error(const char *msg);
void	ft_error_cmd(const char *cmd);
void	ft_error_file(const char *file);
void	ft_error_argc(int argc);

/* pipex functions */
void	process_child(char *argv[], char *envp[], int pipefd[], int infile);
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile);
char	*get_cmd_path(char *cmd, char *envp[]);

#endif
