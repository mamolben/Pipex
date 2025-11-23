/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:02:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 17:03:42 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ======= Standard C Library ======= */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ======= Funciones Libft ======= */
/* libft_string.c */
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

/* ======= libft_split.c ======= */
size_t	count_substr(const char *s, char c);
void	free_split(char **array, size_t idx);
char	*copy_substr(const char *start, char c);
int		fill_array(char **array, const char *s, char c, size_t count);
char	**ft_split(const char *str, char car);

/* ======= libft_mem_comp.c ======= */
void	ft_free(char **str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ======= libft_fd.c ======= */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s, int fd);

/* ======= handling error.c  ======= */
void	ft_error(const char *msg);
void	ft_error_cmd(const char *cmd);
void	ft_error_file(const char *file);
void	ft_error_argc(int argc);

/* ======= management path.c ======= */
char	*join_path(char *dir, char *cmd);
char	*find_path_env(char *envp[]);
char	*get_path(char *cmd, char **envp);

/* ======= core pipex.c  ======= */
void	process_child(char *argv[], char *envp[], int pipefd[], int infile);
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile);
void	init_fds(char *argv[], int *infile, int *outfile);
void	execute(char *argv[], char *envp[], int infile, int outfile);

#endif
