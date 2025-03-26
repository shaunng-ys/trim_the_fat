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

// char *string_check(char **leftover, char **placeholder1, char **placeholder2, char **buffer)
// {
// 	size_t	i;
// 	size_t	m;

// 	i = -1;
// 	m = 0;
// 	while ((*leftover)[m] != '\n' && (*leftover)[m])
// 		m++;
// 	*placeholder1 = ft_calloc(m + 2, sizeof(char));
// 	while (++i < m)
// 		(*placeholder1)[i] = (*leftover)[i];
// 	if ((*leftover)[m] == '\n')
// 	{
// 		(*placeholder1)[i] = '\n';
// 		free(*placeholder2);
// 		*placeholder2 = ft_calloc(strlen(*leftover) - m + 1, sizeof(char));
// 		i = 0;
// 		while ((*leftover)[++m])
// 			(*placeholder2)[i++] = (*leftover)[m];
// 		free(*leftover);
// 		*leftover = ft_calloc(strlen(*placeholder2) + 1, sizeof(char));
// 		copier((*leftover), (*placeholder2), '\0');
// 		free(*buffer);
// 		free(*placeholder2);
// 		return (*placeholder1);
// 	}
// 	return (NULL);
// }

char *string_check(char **leftover, t_gnl *a)
{
	size_t	i;
	size_t	m;

	i = -1;
	m = 0;
	while ((*leftover)[m] != '\n' && (*leftover)[m])
		m++;
	a->placeholder1 = ft_calloc(m + 2, sizeof(char));
	while (++i < m)
		(a->placeholder1)[i] = (*leftover)[i];
	if ((*leftover)[m] == '\n')
	{
		(a->placeholder1)[i] = '\n';
		free(a->placeholder2);
		a->placeholder2 = ft_calloc(ft_strlen(*leftover) - m + 1, sizeof(char));
		i = 0;
		while ((*leftover)[++m])
			(a->placeholder2)[i++] = (*leftover)[m];
		free(*leftover);
		*leftover = ft_calloc(ft_strlen(a->placeholder2) + 1, sizeof(char));
		copier((*leftover), (a->placeholder2), '\0');
		return (free(a->buffer), free(a->placeholder2), a->placeholder1);
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
			free(a->placeholder1);
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

char *new_line_split(char **leftover, char **buffer, char **placeholder1, char **placeholder2)
{
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	l = 0;
	k = 0;
	free(*placeholder2);
	*placeholder2 = ft_calloc(ft_strlen(*placeholder1) + 1, 1);
	i = copier((*placeholder2), (*placeholder1), '\n');
	(*placeholder2)[i] = '\n';
	l = ++i;
	if ((*placeholder1)[l])
	{
		while ((*placeholder1)[l++])
			k++;
		*leftover = ft_calloc(k + 2, sizeof(char));
		k = 0;
		while ((*placeholder1)[i])
			(*leftover)[k++] = (*placeholder1)[i++];
	}
	free(*placeholder1);
	free(*buffer);
	return (*placeholder2);
}

char	*getme_a_nl(int readvalue, int fd,  char **leftover, t_gnl *a)
{
	a->i = 0;
	a->n = 0;
	while (readvalue > 0)
	{
		a->ptr = if_else(&readvalue, &fd, &leftover, a);
		if (a->ptr != NULL)
			return (a->placeholder1);
		else if ((readvalue == 0 && *leftover == NULL) || readvalue < 0)
			return (NULL);
		free(a->placeholder2);
		a->placeholder2 = ft_calloc(ft_strlen(a->placeholder1) + 1, 1);
		if (ft_strlen(a->placeholder1) > 0)
			copier(a->placeholder2, a->placeholder1, '\0');
		free(a->placeholder1);
		a->placeholder1 = ft_calloc(ft_strlen(a->placeholder2) + ft_strlen(a->buffer) + 1, 1);
		if (ft_strlen(a->placeholder2) > 0)
			copier(a->placeholder1, a->placeholder2, '\0');
		a->n = ft_strlen(a->placeholder2);
		while ((a->buffer)[a->i])
			a->placeholder1[a->n++] = (a->buffer)[a->i++];
		a->i = 0;
		if (buffer_check(a->buffer, ft_strlen(a->buffer)) > 0)
			return (new_line_split(&(*leftover), &(a->buffer), &(a->placeholder1), &(a->placeholder2)));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	t_gnl a;
	a.readvalue = 5;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	a.buffer = malloc(BUFFER_SIZE + 1);
	a.placeholder1 = malloc(BUFFER_SIZE + 1);
	a.placeholder2 = malloc(BUFFER_SIZE + 1);
	((char *)a.buffer)[0] = '\0';
	((char *)a.placeholder1)[0] = '\0';
	((char *)a.placeholder2)[0] = '\0';
	a.ohana = leftover_checker(&leftover, &a);
	if (a.ohana != NULL && ft_strlen(a.ohana) > 0)
	{
		a.placeholder1 = a.ohana;
		return (a.placeholder1);
	}
	a.placeholder = getme_a_nl(a.readvalue, fd, &leftover, &a);
	if (a.placeholder != NULL && ft_strlen(a.placeholder) > 0)
		return (a.placeholder);
	else if (a.placeholder == NULL)
		return (free(leftover), NULL);
	return (free(a.placeholder1), free(a.placeholder2), free(a.buffer), NULL);
}
