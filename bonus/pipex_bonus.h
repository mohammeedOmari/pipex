/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momari <momari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:28:45 by momari            #+#    #+#             */
/*   Updated: 2024/01/16 09:21:32 by momari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H 
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_free(char **str);
char	*get_path(char *av, char **env);
char	*ft_getjoin(char *s1, char *s2);
int		ft_search(char *str);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dst, char const *src, size_t len);
void	ft_handle_error(int n, char *str);
void	ft_close2file(int fd1, int fd2);
void	ft_her_doc(char **av, char **env);
void	first_command(char **av, char **env, int n, int *fd_stdin);
void	last_command(char **av, char **env, int ac, int fd);
void	ft_fille_file(char **av, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	exec_command(char *av, char **env);
void	last_command_here(char **av, char **env, int ac, int fd);

#endif
