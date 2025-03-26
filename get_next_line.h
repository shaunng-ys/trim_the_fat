/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:57:19 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:57:21 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

typedef struct s_gnl{
	int			readvalue;
	char		*buffer;
	char		*ohana;
	char		*placeholder;
	char		*placeholder1;
	char		*placeholder2;
}	t_gnl;

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
size_t	copier(char	*dest, char *src, char limiter);
int		buffer_check(char *buffer, size_t index);
char	*new_line_split(char **leftover, char **buffer, char **placeholder1, char **placeholder2);
char	*if_else(char **buffer, int *readvalue_ptr, int *fd_ptr, char ***leftover, char **placeholder1, char **placeholder2);
char	*getme_a_nl(int readvalue, int fd, char *buffer, char *placeholder1, char *placeholder2, char **leftover);
#endif