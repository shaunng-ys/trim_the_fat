/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:56:36 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:56:38 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// int	main(void)
// {
// 	size_t	n;
// 	char	*line;
// 	n = open("multiple_line_no_nl.txt", O_RDONLY);
// 	FILE*	ptr = fopen("multiple_line_no_nl.txt", "r");
// 	fseek(ptr, 0, SEEK_SET);
// 	line = get_next_line(n);
// 	while (line)
// 	{
// 		printf("Line returned from gnl: %s\n", line);
// 		free(line);
// 		line = get_next_line(n);
// 	}
// 	return (0);
// }

char *string_check(char **leftover, t_gnl *a)
{
	size_t	i;
	size_t	m;

	i = -1;
	m = 0;
	while ((*leftover)[m] != '\n' && (*leftover)[m])
		m++;
	a->ph1 = ft_calloc(m + 2, sizeof(char));
	while (++i < m)
		(a->ph1)[i] = (*leftover)[i];
	if ((*leftover)[m] == '\n')
	{
		(a->ph1)[i] = '\n';
		free(a->ph2);
		a->ph2 = ft_calloc(ft_strlen(*leftover) - m + 1, sizeof(char));
		i = 0;
		while ((*leftover)[++m])
			(a->ph2)[i++] = (*leftover)[m];
		free(*leftover);
		*leftover = ft_calloc(ft_strlen(a->ph2) + 1, sizeof(char));
		copier((*leftover), (a->ph2), '\0');
		return (free(a->buffer), free(a->ph2), a->ph1);
	}
	return (NULL);
}

char *leftover_checker(char **leftover, t_gnl *a)
{
	char	*result;

	if (*leftover != NULL)
	{
		if ((*leftover)[0] != '\0')
		{
			free(a->ph1);
			result = string_check(leftover, a);
			if (result != NULL && ft_strlen(result) > 0)
				return (result);
			else
			{
				free(*leftover);
				*leftover = NULL;
				return (NULL);
			}
		}
		if (*leftover != NULL && (*leftover)[0] == '\0')
		{
			free(*leftover);
			*leftover = NULL;
		}
	}
	return (NULL);
}

char *nl_split(char **leftover, char **buffer, char **ph1, char **ph2)
{
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	l = 0;
	k = 0;
	free(*ph2);
	*ph2 = ft_calloc(ft_strlen(*ph1) + 1, 1);
	i = copier((*ph2), (*ph1), '\n');
	(*ph2)[i] = '\n';
	l = ++i;
	if ((*ph1)[l])
	{
		while ((*ph1)[l++])
			k++;
		*leftover = ft_calloc(k + 2, sizeof(char));
		k = 0;
		while ((*ph1)[i])
			(*leftover)[k++] = (*ph1)[i++];
	}
	free(*ph1);
	free(*buffer);
	return (*ph2);
}

char	*getme_a_nl(int rv, int fd,  char **leftover, t_gnl *a)
{
	a->i = 0;
	a->n = 0;
	while (rv > 0)
	{
		a->ptr = if_else(&rv, &fd, &leftover, a);
		if (a->ptr != NULL)
			return (a->ph1);
		else if ((rv == 0 && *leftover == NULL) || rv < 0)
			return (NULL);
		free(a->ph2);
		a->ph2 = ft_calloc(ft_strlen(a->ph1) + 1, 1);
		if (ft_strlen(a->ph1) > 0)
			copier(a->ph2, a->ph1, '\0');
		free(a->ph1);
		a->ph1 = ft_calloc(ft_strlen(a->ph2) + ft_strlen(a->buffer) + 1, 1);
		if (ft_strlen(a->ph2) > 0)
			copier(a->ph1, a->ph2, '\0');
		a->n = ft_strlen(a->ph2);
		while ((a->buffer)[a->i])
			a->ph1[a->n++] = (a->buffer)[a->i++];
		a->i = 0;
		if (buffer_check(a->buffer, ft_strlen(a->buffer)) > 0)
			return (nl_split(&(*leftover), &(a->buffer), &(a->ph1), &(a->ph2)));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	t_gnl a;
	a.rv = 5;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	a.buffer = malloc(BUFFER_SIZE + 1);
	a.ph1 = malloc(BUFFER_SIZE + 1);
	a.ph2 = malloc(BUFFER_SIZE + 1);
	((char *)a.buffer)[0] = '\0';
	((char *)a.ph1)[0] = '\0';
	((char *)a.ph2)[0] = '\0';
	a.ohana = leftover_checker(&leftover, &a);
	if (a.ohana != NULL && ft_strlen(a.ohana) > 0)
	{
		a.ph1 = a.ohana;
		return (a.ph1);
	}
	a.ph = getme_a_nl(a.rv, fd, &leftover, &a);
	if (a.ph != NULL && ft_strlen(a.ph) > 0)
		return (a.ph);
	else if (a.ph == NULL)
		return (free(leftover), NULL);
	return (free(a.ph1), free(a.ph2), free(a.buffer), NULL);
}
