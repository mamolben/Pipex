/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:02:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/20 21:13:25 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*Library standard*/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

char    *get_next_line(int fd);


/*Library personal*/

/* libft_string.c */
size_t  ft_strlen(const char *str);
char    *ft_strdup(const char *str);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);
char    *ft_strjoin(char const *s1, char const *s2);

/* libft_mem_dup.c */
void    ft_free(char **str);
int     ft_strncmp(const char *s1, const char *s2, size_t n);

/* libft_split.c */
char **ft_split(const char *str, char car);

/* error.c */
void	ft_error(const char *msg);
void	ft_error_cmd(const char *cmd);
void	ft_error_file(const char *file);
void	ft_error_argc(int argc);

/* path */
char    *join_path(char *dir, char *cmd);
char    *get_cmd_path(char *cmd, char *envp[]);

/* pipex functions */
void	process_child(char *argv[], char *envp[], int pipefd[], int infile);
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile);

#endif
