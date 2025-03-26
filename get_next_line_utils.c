/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:56:54 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:56:56 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p2s;
	size_t	n;
	size_t	i;

	i = 0;
	n = (count * size);
	if (count == 0 || size == 0)
	{
		p2s = malloc(1);
		(((char *)p2s)[0] = 0);
		return (p2s);
	}
	if (size >= INT_MAX / count)
		return (NULL);
	p2s = malloc(count * size);
	if (p2s == 0)
		return (NULL);
	while (n--)
		((char *)p2s)[i++] = '\0';
	return (p2s);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	copier(char	*dest, char *src, char limiter)
{
	size_t	i;

	i = 0;
	while (src[i] != limiter)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

int	buffer_check(char *buffer, size_t index)
{
	size_t	i;

	i = 0;
	while (index--)
	{
		if (((char *)buffer)[i] == '\n')
			return (i + 2);
		else
			i++;
	}
	return (0);
}

char	*if_else(int *rv_ptr, int *fd_ptr, char ***leftover, t_gnl *a)
{
	size_t	buffer_size;
	size_t	i;

	buffer_size = BUFFER_SIZE + 1;
	i = 0;
	if (ft_strlen(a->buffer) > 0)
	{
		free(a->buffer);
		a->buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	}
	else
		while (buffer_size--)
			(a->buffer)[i++] = '\0';
	*rv_ptr = read(*fd_ptr, a->buffer, BUFFER_SIZE);
	if (*rv_ptr == 0 && ft_strlen(a->ph1) > 0)
		return (free(a->buffer), free(a->ph2), a->ph1);
	else if ((*rv_ptr == 0 && **leftover == NULL) || *rv_ptr < 0)
		return (free(a->ph1), free(a->ph2), free(a->buffer), NULL);
	return (NULL);
}
