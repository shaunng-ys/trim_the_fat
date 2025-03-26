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

void	ft_bzero(char *s, size_t n)
{
	int	i;

	i = 0;
	while (n)
	{
		s[i] = 0;
		i++;
		n--;
	}
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

char	*if_else(char **buffer, int *readvalue_ptr, int *fd_ptr, char ***leftover, char **placeholder1, char **placeholder2)
{
	if (strlen(*buffer) > 0)
	{
		free(*buffer);
		*buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	}
	else
		ft_bzero(*buffer, BUFFER_SIZE + 1);
	*readvalue_ptr = read(*fd_ptr, *buffer, BUFFER_SIZE);
	if (*readvalue_ptr == 0 && strlen(*placeholder1) > 0)
	{
		free(*buffer);
		free(*placeholder2);
		return (*placeholder1);
	}
	else if (*readvalue_ptr == 0 && **leftover == NULL)
	{
		free(*placeholder1);
		free(*placeholder2);
		free(*buffer);
		return (NULL);
	}
	else if (*readvalue_ptr < 0)
		return (free(*buffer), free(*placeholder1), free(*placeholder2), NULL);
	return (NULL);
}
